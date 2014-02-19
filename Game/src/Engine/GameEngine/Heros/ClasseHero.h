#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_HEROS_CLASSEHERO_HPP__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_HEROS_CLASSEHERO_HPP__

#include <string>
#include <map>
#include "../Unites/TypeUnite.h"

class Faction;
class HeroMesh;

class ClasseHero: public TypeUnite
{
public:
    struct HeroMesh{
        std::string mesh;
        std::string walk;
        std::string jump;
        std::string fall;
    };
    ClasseHero(int, Faction*,const boost::property_tree::ptree &data);
    int id() const;
    const std::string& icone() const;
    const HeroMesh* mesh(int level) const;
    void addMesh(int from, int to, const HeroMesh&);
private:
    std::string m_icone;
    struct levelRange{
        int from,
            to;
        bool operator<(const levelRange& o) const
        {
            return o.from>from;
        }
    };
    std::map<levelRange, HeroMesh> m_meshes;
    friend class Faction;
};

#endif
