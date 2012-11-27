#ifndef TYPEUNITE_H
#define TYPEUNITE_H

#include "typedefs.h"
#include "../Ressources/Ressources.h"
#include <string>
#include <vector>

class Faction;
class Recherche;
class Armure;
class Degat;
class TypeUnite
{
    public:
        enum Type{
            TERRESTE,
            AERIEN,
            BATIMENT
        };
        struct MeshParameters{
            std::string m_nomMesh;
        };
        TypeUnite(UnitId id, Type, Faction* fac);
        virtual ~TypeUnite();

        static Type typeFromString(const std::string&);

    private:
        friend class Faction;
        const UnitId m_id;
        Type m_type;
        Faction *m_fation;

        int m_vie;
        std::string m_nom;
        Ressources m_cout, m_apports;
        int m_temps_construction;
        int m_attaque;
        float m_vision, m_portee;
        TypeUnite* m_amelioration;
        std::vector<TypeUnite*> m_construit;
        std::vector<Recherche*> m_recherches;
        std::vector<Recherche*> m_necessiteRecherche;
        std::vector<TypeUnite*> m_necessiteUnite;
        int m_niveau_recquis;
        Degat *m_typeDegats;
        Armure *m_armure;
        MeshParameters m_meshParameters;
};

#endif // TYPEUNITE_H
