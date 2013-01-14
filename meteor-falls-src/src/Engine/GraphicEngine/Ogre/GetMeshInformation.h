#ifndef GETMESHINFORMATION_H_INCLUDED
#define GETMESHINFORMATION_H_INCLUDED
#include <OgreRay.h>
#include <OgreSceneQuery.h>

// Get the mesh information for the given mesh.
// Code found in Wiki: www.ogre3d.org/wiki/index.php/RetrieveVertexData
void GetMeshInformation(const Ogre::MeshPtr mesh,
                                size_t &vertex_count,
                                Ogre::Vector3* &vertices,
                                size_t &index_count,
                                unsigned long* &indices,
                                const Ogre::Vector3 &position,
                                const Ogre::Quaternion &orient,
                                const Ogre::Vector3 &scale);
Ogre::Entity* findFirstPicking(Ogre::Ray&, Ogre::RaySceneQuery*);

#endif // GETMESHINFORMATION_H_INCLUDED
