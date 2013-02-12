#ifndef JOUEURRPG_H
#define JOUEURRPG_H

class Joueur;
class JoueurRPG 
{
    public:
        JoueurRPG(Joueur*);
        virtual ~JoueurRPG();
		Joueur* joueur() const;

    private:
		Joueur *m_joueur;
};

#endif // JOUEURRPG_H
