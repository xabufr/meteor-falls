#ifndef FACTION_H
#define FACTION_H
#include <string>
#include <unordered_map>
#include <vector>
#include "../Unites/typedefs.h"

typedef unsigned char FactionId;
typedef unsigned short RechercheId;
class TypeUnite;
class Recherche;
class Faction
{
    public:
        Faction(bool jouable, FactionId id, const std::string& nom);
        virtual ~Faction();

        FactionId id() const;

        void addConfigFile(std::string path);

        /** \brief Charge tous les fichiers passés via addConfigFile()
         */
        void load();
        TypeUnite* getType(UnitId);
    protected:
    private:
        const std::string m_nom;
        const FactionId m_id;
        const bool m_jouable;
        std::unordered_map<UnitId, TypeUnite*> m_typesUnites;
        std::unordered_map<RechercheId, Recherche*> m_recherches;
        std::vector<std::string> m_paths;
        std::vector<std::string> m_batiments;
        std::vector<std::string> m_terrestre;
        std::vector<std::string> m_aerien;
};

#endif // FACTION_H
