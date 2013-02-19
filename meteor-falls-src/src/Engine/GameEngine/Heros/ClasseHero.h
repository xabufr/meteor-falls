#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_HEROS_CLASSEHERO_HPP__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_HEROS_CLASSEHERO_HPP__

#include <string>
#include <map>

class Faction;
class ClasseHero
{
public:
	ClasseHero(int, Faction*);
	int id() const;
	const std::string& icone() const;
	const std::string& nom() const;
	std::string mesh(int level) const;
	Faction* faction() const;
	void addMesh(int from, int to, const std::string&);
private:
	int m_id;
	std::string m_icone, m_nom;
	Faction *m_faction;
	struct levelRange{
		int from,
			to;
		bool operator<(const levelRange& o) const
		{
			return o.from>from;
		}
	};
	std::map<levelRange, std::string> m_meshes;
	friend class Faction;
};

#endif 
