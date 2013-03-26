#include "ClasseHero.h"

ClasseHero::ClasseHero(int id, Faction* fac): 
TypeUnite(id, TypeUnite::HERO, fac)
{
}
int ClasseHero::id() const
{
	return m_id;
}
const std::string& ClasseHero::icone() const
{
	return m_icone;
}
const ClasseHero::HeroMesh* ClasseHero::mesh(int level) const
{
	for(auto &mesh : m_meshes)
	{
		if(mesh.first.from<=level&&mesh.first.to>=level)
			return &mesh.second;
	}
	return nullptr;
}
void ClasseHero::addMesh(int from, int to, const HeroMesh& hm)
{
	for(auto it : m_meshes)
	{
		if(it.first.from<=from && it.first.to >= to)
			return;
	}
	levelRange range;
	range.from      = from;
	range.to        = to;
	m_meshes[range] = hm;
}
