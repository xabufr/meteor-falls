#ifndef EQUIPE_H
#define EQUIPE_H

#include <vector>

class Faction;
class JoueurRPG;
class JoueurRTS;
class Joueur;

class Equipe
{
    public:
        Equipe(char id);
        virtual ~Equipe();

        Faction* faction();
        void setFaction(Faction*);
		void setJoueurRTS(JoueurRTS*);
		const std::vector<JoueurRPG*> getRPG() const;
		JoueurRTS* getRTS() const;
		char id() const;

		void addRPG(JoueurRPG*);
		void removeRPG(JoueurRPG*);

		void addJoueur(Joueur*);
		void removeJoueur(Joueur*);
		const std::vector<Joueur*> joueurs() const;

    protected:
    private:
        Faction *m_faction;
		std::vector<JoueurRPG*> m_joueursRPS;
		JoueurRTS *m_joueurRTS;
		std::vector<Joueur*> m_joueurs;
		char m_id;
};

#endif // EQUIPE_H
