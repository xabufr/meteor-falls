#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_HEROS_CLASSEHERO_HPP__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_HEROS_CLASSEHERO_HPP__

#include <string>

class Faction;
class ClasseHero
{
public:
	ClasseHero(int, Faction*);
	int id() const;
	const std::string& icone() const;
	const std::string& nom() const;
	Faction* faction() const;
private:
	int m_id;
	std::string m_icone, m_nom;
	Faction *m_faction;
	friend class Faction;
};

#endif 
