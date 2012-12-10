#ifndef EQUIPE_H
#define EQUIPE_H

#include <vector>

class Faction;
class JoueurRPG;
class JoueurRTS;

class Equipe
{
    public:
        Equipe();
        virtual ~Equipe();

        Faction* faction();
        void setFaction(Faction*);
		void setJoueurRTS(JoueurRTS*);

    protected:
    private:
        Faction *m_faction;
		std::vector<JoueurRPG*> m_joueursRPS;
		JoueurRTS *m_joueurRTS;
};

#endif // EQUIPE_H
