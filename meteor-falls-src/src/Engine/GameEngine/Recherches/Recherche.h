#ifndef RECHERCHE_H
#define RECHERCHE_H

#include "../Ressources/Ressources.h"
#include <vector>
#include <string>

typedef unsigned short RechercheId;
class TypeUnite;
class Recherche
{
    public:
        Recherche(RechercheId);
        virtual ~Recherche();
    protected:
    private:
        friend class Faction;
        int m_temps;
        Ressources m_cout;
        std::string m_icone, m_script, m_nom;
        const RechercheId m_id;

        std::vector<TypeUnite*> m_unitesNecessaires;
        std::vector<Recherche*> m_recherchesNecessaires;
        int m_niveau_recquis;
};

#endif // RECHERCHE_H
