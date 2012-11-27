#include "GetMeshInformation.h"

// Get the mesh information for the given mesh.
// Code found in Wiki: www.ogre3d.org/wiki/index.php/RetrieveVertexData
void GetMeshInformation(const Ogre::MeshPtr mesh,
                                size_t &vertex_count,
                                Ogre::Vector3* &vertices,
                                size_t &index_count,
                                unsigned long* &indices,
                                const Ogre::Vector3 &position,
                                const Ogre::Quaternion &orient,
                                const Ogre::Vector3 &scale)
{
    bool added_shared = false;
    size_t current_offset = 0;
    size_t shared_offset = 0;
    size_t next_offset = 0;
    size_t index_offset = 0;

    vertex_count = index_count = 0;

    // Calculate how many vertices and indices we're going to need
    for (unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
    {
        Ogre::SubMesh* submesh = mesh->getSubMesh( i );

        // We only need to add the shared vertices once
        if(submesh->useSharedVertices)
        {
            if( !added_shared )
            {
                vertex_count += mesh->sharedVertexData->vertexCount;
                added_shared = true;
            }
        }
        else
        {
            vertex_count += submesh->vertexData->vertexCount;
        }

        // Add the indices
        index_count += submesh->indexData->indexCount;
    }


    // Allocate space for the vertices and indices
    vertices = new Ogre::Vector3[vertex_count];
    indices = new unsigned long[index_count];

    added_shared = false;

    // Run through the submeshes again, adding the data into the arrays
    for ( unsigned short i = 0; i < mesh->getNumSubMeshes(); ++i)
    {
        Ogre::SubMesh* submesh = mesh->getSubMesh(i);

        Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

        if((!submesh->useSharedVertices)||(submesh->useSharedVertices && !added_shared))
        {
            if(submesh->useSharedVertices)
            {
                added_shared = true;
                shared_offset = current_offset;
            }

            const Ogre::VertexElement* posElem =
                vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

            Ogre::HardwareVertexBufferSharedPtr vbuf =
                vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

            unsigned char* vertex =
                static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

            // There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
            //  as second argument. So make it float, to avoid trouble when Ogre::Real will
            //  be comiled/typedefed as double:
            //      Ogre::Real* pReal;
            float* pReal;

            for( size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
            {
                posElem->baseVertexPointerToElement(vertex, &pReal);

                Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

                vertices[current_offset + j] = (orient * (pt * scale)) + position;
            }

            vbuf->unlock();
            next_offset += vertex_data->vertexCount;
        }


        Ogre::IndexData* index_data = submesh->indexData;
        size_t numTris = index_data->indexCount / 3;
        Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
        if( ibuf.isNull() ) continue; // need to check if index buffer is valid (which will be not if the mesh doesn't have triangles like a pointcloud)

        bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

        unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
        unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);


        size_t offset = (submesh->useSharedVertices)? shared_offset : current_offset;
        size_t index_start = index_data->indexStart;
        size_t last_index = numTris*3 + index_start;

        if (use32bitindexes)
            for (size_t k = index_start; k < last_index; ++k)
            {
                indices[index_offset++] = pLong[k] + static_cast<unsigned long>( offset );
            }

        else
            for (size_t k = index_start; k < last_index; ++k)
            {
                indices[ index_offset++ ] = static_cast<unsigned long>( pShort[k] ) +
                    static_cast<unsigned long>( offset );
            }

        ibuf->unlock();
        current_offset = next_offset;
    }
}
Ogre::Entity* findFirstPicking(Ogre::Ray& ray, Ogre::RaySceneQuery* sceneQuery)
{
    Ogre::Entity *ret=0;
    sceneQuery->setRay(ray);
    sceneQuery->setSortByDistance(true);

    Ogre::RaySceneQueryResult& result = sceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator it;
    Ogre::SceneNode *current;
    bool found = false;
    for(it = result.begin();it!=result.end()&&!found;++it)
    {
        if(it->movable!=NULL&&it->movable->getMovableType().compare("Entity")==0)
        {
            current = it->movable->getParentSceneNode();

            size_t vertCount, indexCount;
            unsigned long* indices;
            Ogre::Vector3* vertices;
            GetMeshInformation(static_cast<Ogre::Entity*>(it->movable)->getMesh(),
                                vertCount,
                                vertices,
                                indexCount,
                                indices,
                                current->getPosition(),
                                current->getOrientation(),
                                current->getScale());

            for(size_t i=0;i<indexCount;i+=3)
            {
                std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray,
                                                                         vertices[indices[i]],
                                                                         vertices[indices[i+1]],
                                                                         vertices[indices[i+2]],
                                                                         true,
                                                                         false);
                if(hit.first)
                {
                    ret = static_cast<Ogre::Entity*>(it->movable);
                    found=true;
                    break;
                }
            }
            delete[] vertices;
            delete[] indices;
        }
    }
    return ret;
}
