#include "Equipe.h"
#include "../Unites/TypeUnite.h"
#include "../Unites/Unite.h"
#include "../Joueur/JoueurRPG.h"
#include "../Unites/UniteFactory.h"
#include <Utils/timeduration.h>

Equipe::Equipe(GameEngine *g, char i): m_id(i), m_game(g)
{
    m_joueurRTS = nullptr;
    m_factory = nullptr;
}
Equipe::~Equipe()
{
    delete m_factory;
}
Faction *Equipe::faction()
{
    return m_faction;
}
void Equipe::setFaction(Faction *f)
{
    m_faction = f;
}
void Equipe::addUnit(Unite *u)
{
    if (u->type() && u->type()->type() == TypeUnite::Type::BATIMENT)
    {
        m_batiments_cache.insert(u->type());
    }
    m_unites_construites.push_back(u);
}
void Equipe::removeUnit(Unite *u)
{
    const TypeUnite *type = u->type();
    m_unites_construites.erase(std::find(m_unites_construites.begin(), m_unites_construites.end(), u));

    if (type && type->type() == TypeUnite::Type::BATIMENT)
    {
        bool typeExistsAnymore = false;
        for (auto it = m_unites_construites.begin(); it != m_unites_construites.end(); ++it)
        {
            if ((*it)->type() == type)
            {
                typeExistsAnymore = true;
                break;
            }
        }
        if(!typeExistsAnymore)
            m_batiments_cache.erase(type);
    }
}
void Equipe::setJoueurRTS(JoueurRTS *joueur)
{
    m_joueurRTS = joueur;
}
const std::vector<JoueurRPG *> Equipe::getRPG() const
{
    return m_joueursRPS;
}
JoueurRTS *Equipe::getRTS() const
{
    return m_joueurRTS;
}
char Equipe::id() const
{
    return m_id;
};
void Equipe::removeRPG(JoueurRPG *j)
{
    for (auto it = m_joueursRPS.begin(); it != m_joueursRPS.end(); ++it)
    {
        if (j->joueur() == (*it)->joueur())
        {
            m_joueursRPS.erase(it);
            return;
        }
    }
}
void Equipe::addRPG(JoueurRPG *j)
{
    for (JoueurRPG * jt : m_joueursRPS)
        if (jt->joueur() == j->joueur())
            return;
    m_joueursRPS.push_back(j);
}
void Equipe::addJoueur(Joueur *j)
{
    for (Joueur * jt : m_joueurs)
        if (jt == j)
            return;
    m_joueurs.push_back(j);
}
void Equipe::removeJoueur(Joueur *j)
{
    for (auto it = m_joueurs.begin(); it != m_joueurs.end(); ++it)
    {
        if (*it == j)
        {
            m_joueurs.erase(it);
            return;
        }
    }
}
const std::vector<Joueur *> Equipe::joueurs() const
{
    return m_joueurs;
}
UniteFactory *Equipe::factory() const
{
    return m_factory;
}
void Equipe::setFactory(UniteFactory *fac)
{
    m_factory = fac;
}
const std::vector<Unite *> &Equipe::unites() const
{
    return m_unites_construites;
}
Unite *Equipe::getUnite(int id) const
{
    for (Unite * u : m_unites_construites)
    {
        if (u->id() == id)
            return u;
    }
    return nullptr;
}
GameEngine *Equipe::game() const
{
    return m_game;
}

bool Equipe::canBuild(const TypeUnite *type) const
{
    for (TypeUnite * typeNecessaire : type->necessiteUnite())
    {
        if(typeNecessaire->type() == TypeUnite::BATIMENT)
            if(m_batiments_cache.find(typeNecessaire) == m_batiments_cache.end())
                return false;
    }
    return type->cout() <= m_ressources;
}
void Equipe::update(const TimeDuration &duration)
{
    for (std::vector<Unite *>::iterator it = m_unites_construites.begin(); it != m_unites_construites.end();)
    {
        if ((*it)->destroyNeeded())
        {
            Unite *u = *it;
            it = m_unites_construites.erase(it);
            delete u;
        }
        else
        {
            (*(it++))->update(duration);
        }
    }
}

const Ressources &Equipe::ressources() const
{
    return m_ressources;
}
