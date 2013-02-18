#ifndef H_AVATAR_H
#define H_AVATAR_H

#include <string>

class ClasseHero;
class Avatar 
{
public:
	Avatar(int, ClasseHero*);
	const std::string& nom() const;
	int id() const;
	ClasseHero* classe() const;
private:
	friend class Faction;
	std::string m_nom;
	ClasseHero *m_classe;
	int m_id;
};

#endif 
