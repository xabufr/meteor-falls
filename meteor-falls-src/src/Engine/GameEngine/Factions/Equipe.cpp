#include "Equipe.h"
#include "../Unites/TypeUnite.h"
#include "../Unites/Unite.h"

Equipe::Equipe()
{
    //ctor
}

Equipe::~Equipe()
{
    //dtor
}
Faction* Equipe::faction()
{
    return m_faction;
}

void Equipe::setFaction(Faction* f)
{
    m_faction=f;
}

void Equipe::create_unit(Unite* u)
{
    bool exists = false;

    if (u->GetType()->type() == TypeUnite::Type::BATIMENT)
    {

        for (int i=0;m_batiments_cache.size();i++)
        {
            if(u->GetType() == m_batiments_cache[i])
                exists == true;
            // batiment deja dans la liste ?
        }

        if (!exists)
            m_batiments_cache.push_back(u->GetType());
    }

        m_unites_construites.push_back(u);


}


void Equipe::destroy_unite(Unite* u)
{

    bool exists = false;

    for(int i = 0; i<m_unites_construites.size() ; i++)
    {
        if (m_unites_construites[i] == u)
        {
            m_unites_construites.erase(m_unites_construites.begin() + i);
        }
    }


    if (u->GetType()->type() == TypeUnite::Type::BATIMENT)
    {

        for (int i=0;m_batiments_cache.size();i++)
        {
            if(u->GetType() == m_batiments_cache[i])
            {
                m_batiments_cache.erase(m_batiments_cache.begin() + i);
            }
        }
    }

}
