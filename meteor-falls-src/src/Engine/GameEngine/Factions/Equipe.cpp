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
    if (u->type()&&u->type()->type() == TypeUnite::Type::BATIMENT)
    {
    	bool exists = false;
        for (int i=0;m_batiments_cache.size();i++)
        {
            if(u->type() == m_batiments_cache[i])
			{
                exists == true;
				break;
			}
            // batiment deja dans la liste ?
        }
        if (!exists)
            m_batiments_cache.push_back(u->type());
    }
    m_unites_construites.push_back(u);
}
void Equipe::destroy_unite(Unite* u)
{

    for(auto it = m_unites_construites.begin(); it!=m_unites_construites.end() ; ++it)
    {
        if (*it == u)
        {
            m_unites_construites.erase(it);
			break;
        }
    }
    if (u->type()&&u->type()->type() == TypeUnite::Type::BATIMENT)
    {
        for (auto it = m_batiments_cache.begin();it!=m_batiments_cache.end();++it)
        {
            if(u->type() == *it)
            {
                m_batiments_cache.erase(it);
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
	for(auto it=m_joueursRPS.begin();it!=m_joueursRPS.end();++it)
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
	for(auto it=m_joueurs.begin();it!=m_joueurs.end();++it)
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
