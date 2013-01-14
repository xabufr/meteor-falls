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

        UnitId id() const;
        Type type() const;
        Faction* fation() const;

        int vie() const;
        const std::string& nom() const;
        const Ressources& cout() const;
        const Ressources& apports() const;
        int temps_construction() const;
        int attaque() const;
        float vision() const;
        float portee() const;
        TypeUnite* amelioration() const;
        const std::vector<TypeUnite*>& construit() const;
        const std::vector<Recherche*>& recherches() const;
        const std::vector<Recherche*>& necessiteRecherche() const;
        const std::vector<TypeUnite*>& necessiteUnite() const;
        int niveau_recquis() const;
        Degat* typeDegats() const;
        Armure* armure() const;
        const MeshParameters& meshParameters() const;

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
