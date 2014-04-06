#ifndef TYPEUNITE_H
#define TYPEUNITE_H

#include "typedefs.h"
#include "../Ressources/Ressources.h"
#include "../Map/WorldObjectType.h"
#include <string>
#include <vector>
#include <map>

class Faction;
class Recherche;
class Armure;
class Degat;
class Avatar;
class TypeUnite: public WorldObjectType
{
    public:
        enum Type{
            TERRESTE,
            AERIEN,
            BATIMENT,
            HERO,
            UNKNOW
        };
        typedef std::map<std::string, std::string> MeshParameters;
        TypeUnite(UnitId id, Type, Faction* fac, const boost::property_tree::ptree &data);
        virtual ~TypeUnite();

        static Type typeFromString(const std::string&);

        UnitId id() const;
        Type type() const;
        Faction* faction() const;

        int vie() const;
        const std::string& nom() const;
        const Ressources& cout() const;
        const Ressources& apports() const;
        float temps_construction() const;
        int attaque() const;
        float vision() const;
        float portee() const;
        bool spawn() const;
        TypeUnite* amelioration() const;
        const std::vector<TypeUnite*>& construit() const;
        const std::vector<Recherche*>& recherches() const;
        const std::vector<Recherche*>& necessiteRecherche() const;
        const std::vector<TypeUnite*>& necessiteUnite() const;
        int niveau_recquis() const;
        Degat* typeDegats() const;
        Armure* armure() const;
        const MeshParameters& meshParameters() const;

    protected:
        friend class Faction;
        const UnitId m_id;
        Type m_type;
        Faction *m_faction;

        int m_vie;
        std::string m_nom;
        Ressources m_cout, m_apports;
        float m_temps_construction;
        int m_attaque;
        float m_vision, m_portee;
        bool m_spawn;
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
