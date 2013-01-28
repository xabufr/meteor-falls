#include "Batiment.h"

Batiment::Batiment(Ogre::SceneManager* mng, int p_id, std::string p_nom, TypeUnite* type, int id)
    : Unite(mng, type, id)
{

    m_timer.reset();
    m_id = p_id;
    m_nom = p_nom;
    m_isconstructed = false;

}

void Batiment::SetPosition(Vector3D p_position)
{

    m_position = p_position;

}

bool Batiment::Is_Constructed()
{
    return m_isconstructed;
}

int Batiment::GetId()
{
    return m_id;
}

std::string Batiment::GetName()
{
    return m_nom;
}

Vector3D Batiment::GetPosition()
{
    return m_position;
}
