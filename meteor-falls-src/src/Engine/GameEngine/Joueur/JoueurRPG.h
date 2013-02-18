#ifndef JOUEURRPG_H
#define JOUEURRPG_H

class Joueur;
class Hero;
class JoueurRPG 
{
    public:
        JoueurRPG(Joueur*);
        virtual ~JoueurRPG();
		Joueur* joueur() const;
		void setHero(Hero*);
		Hero* hero() const;

    private:
		Joueur *m_joueur;
		Hero *m_hero;
};

#endif // JOUEURRPG_H
