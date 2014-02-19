#ifndef FACTION_H
#define FACTION_H
#include <string>
#include <unordered_map>
#include <vector>
#include "../Unites/typedefs.h"
#include "../Heros/ClasseHeroManager.h"
#include "../../ScriptEngine/XmlDocumentManager.h"

typedef unsigned char FactionId;
typedef unsigned short RechercheId;
class TypeUnite;
class Avatar;
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
		const ClasseHeroManager& getClassesManager() const;
		const std::vector<Avatar*> defaultAvatars() const;
		const std::string& nom() const;
    protected:
    private:
        const std::string m_nom;
        const FactionId m_id;
        const bool m_jouable;
		void processUnit(const XmlDocumentManager::Document&);
		ClasseHeroManager m_classeHeroManager;
        std::unordered_map<UnitId, TypeUnite*> m_typesUnites;
        std::unordered_map<RechercheId, Recherche*> m_recherches;
		std::vector<Avatar*> m_avatarDefault;
        std::vector<std::string> m_paths;
};

#endif // FACTION_H
