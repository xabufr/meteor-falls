#ifndef UNITE_H
#define UNITE_H
#include "../Map/ObjetTerrain.h"
#include "TypeUnite.h"
#include "../../../Utils/Vector3D.h"

class Equipe;
class Unite : public ObjetTerrain
{
    public:
        Unite(Ogre::SceneManager*, Equipe* ,TypeUnite* type, int id);
        TypeUnite* GetType();
        virtual ~Unite();
		int id() const;
		TypeUnite* type() const;
	protected:
        Vector3D m_position;
        TypeUnite* m_type;
		int m_id;
		Equipe *m_equipe;
};

#endif // UNITE_H
