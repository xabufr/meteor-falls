#include "ClasseHero.h"

ClasseHero::ClasseHero(int id, Faction* fac): m_id(id), m_faction(fac)
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
const std::string& ClasseHero::nom() const
{
	return m_nom;
}
std::string ClasseHero::mesh(int level) const
{
	for(auto mesh : m_meshes)
	{
		if(mesh.first.from>=level&&mesh.first.to<=level)
			return mesh.second;
	}
	return "";
}
void ClasseHero::addMesh(int from, int to, const std::string& mesh)
{
	for(auto it : m_meshes)
	{
		if(it.first.from<=from && it.first.to >= to)
			return;
	}
	levelRange range;
	range.from      = from;
	range.to        = to;
	m_meshes[range] = mesh;
}
