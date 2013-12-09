#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_HEROS_CLASSEHEROMANAGER_HPP__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_GAMEENGINE_HEROS_CLASSEHEROMANAGER_HPP__

#include <vector>
#include <cstddef>

class ClasseHero;
class ClasseHeroManager
{
public:
	~ClasseHeroManager();
	ClasseHero* classe(int) const;
	const std::vector<ClasseHero*>& classes() const;
	bool addClasse(ClasseHero*);
	size_t count() const;
private:
	std::vector<ClasseHero*> m_classes;
};

#endif 
