#ifndef EQUIPE_H
#define EQUIPE_H

#include <vector>

class Faction;
class JoueurRPG;
class JoueurRTS;

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

    protected:
    private:
        Faction *m_faction;
		std::vector<JoueurRPG*> m_joueursRPS;
		JoueurRTS *m_joueurRTS;
		char m_id;
};

#endif // EQUIPE_H
