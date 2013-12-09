#include "ClasseHeroManager.h"
#include "ClasseHero.h"

ClasseHeroManager::~ClasseHeroManager()
{
	for(ClasseHero *cl : m_classes)
		delete cl;
}
bool ClasseHeroManager::addClasse(ClasseHero* cla)
{
	for(ClasseHero *cl : m_classes)
		if(cl->id() == cla->id())
			return false;
	m_classes.push_back(cla);
	return true;
}
ClasseHero* ClasseHeroManager::classe(int id) const
{
	for(ClasseHero* cl : m_classes)
		if(cl->id() == id)
			return cl;
	return nullptr;
}
size_t ClasseHeroManager::count() const
{
	return m_classes.size();
}
const std::vector<ClasseHero*>& ClasseHeroManager::classes() const
{
	return m_classes;
}
