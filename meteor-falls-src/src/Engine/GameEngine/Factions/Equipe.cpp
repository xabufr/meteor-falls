#include "Equipe.h"
#include "../Unites/TypeUnite.h"
#include "../Unites/Unite.h"
#include "../Joueur/JoueurRPG.h"
#include "../Unites/UniteFactory.h"

Equipe::Equipe(char i): m_id(i)
{
	m_joueurRTS=nullptr;
    m_factory = new UniteFactory(this);
}
Equipe::~Equipe()
{
	delete m_factory;
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
    if (u->GetType()->type() == TypeUnite::Type::BATIMENT)
    {
    	bool exists = false;
        for (int i=0;m_batiments_cache.size();i++)
        {
            if(u->GetType() == m_batiments_cache[i])
			{
                exists == true;
				break;
			}
            // batiment deja dans la liste ?
        }
        if (!exists)
            m_batiments_cache.push_back(u->GetType());
    }
    m_unites_construites.push_back(u);
}
void Equipe::destroy_unite(Unite* u)
{
    for(size_t i = 0; i<m_unites_construites.size() ; i++)
    {
        if (m_unites_construites[i] == u)
        {
            m_unites_construites.erase(m_unites_construites.begin() + i);
			break;
        }
    }
    if (u->GetType()->type() == TypeUnite::Type::BATIMENT)
    {

        for (int i=0;m_batiments_cache.size();i++)
        {
            if(u->GetType() == m_batiments_cache[i])
            {
                m_batiments_cache.erase(m_batiments_cache.begin() + i);
				break;
            }
        }
    }
}
void Equipe::setJoueurRTS(JoueurRTS* joueur)
{
	m_joueurRTS = joueur;
}
const std::vector<JoueurRPG*> Equipe::getRPG() const
{
	return m_joueursRPS;
}
JoueurRTS* Equipe::getRTS() const
{
	return m_joueurRTS;
}
char Equipe::id() const
{
	return m_id;
};
void Equipe::removeRPG(JoueurRPG* j)
{
	for(auto it=m_joueursRPS.begin();it!=m_joueursRPS.end();)
	{
		if(j->joueur()==(*it)->joueur())
		{
			m_joueursRPS.erase(it);
			return;
		}
	}
}
void Equipe::addRPG(JoueurRPG* j)
{
	for(JoueurRPG *jt : m_joueursRPS)
		if(jt->joueur()==j->joueur())
			return;
	m_joueursRPS.push_back(j);
}
void Equipe::addJoueur(Joueur* j)
{
	for(Joueur* jt : m_joueurs)
		if(jt==j)
			return;
	m_joueurs.push_back(j);
}
void Equipe::removeJoueur(Joueur* j)
{
	for(auto it=m_joueurs.begin();it!=m_joueurs.end();)
	{
		if(*it==j)
		{
			m_joueurs.erase(it);
			return;
		}
	}
}
const std::vector<Joueur*> Equipe::joueurs() const
{
	return m_joueurs;
}
UniteFactory* Equipe::factory()
{
	return m_factory;
}
const std::vector<Unite*>& Equipe::unites() const
{
	return m_unites_construites;
}
Unite* Equipe::getUnite(int id) const
{
	for(Unite *u : m_unites_construites)
	{
		if(u->id() == id)
			return u;
	}
	return nullptr;	
}
