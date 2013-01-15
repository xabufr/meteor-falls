#ifndef JOUEUR_H
#define JOUEUR_H
#include <string>
#include "JoueurRPG.h"
#include "JoueurRTS.h"

class Equipe;
class Joueur
{
    public:
        enum Type{
            LAN,
            WAN,
            NONE
        };
        enum TypeGameplay{
            RTS,
            RPG
        };
        Joueur();
        virtual ~Joueur();
        virtual const Type getType(){return Type::NONE;};
		void setNom(const std::string&);
		const std::string& getNom();
		void setNumSession(const std::string&);
		const std::string& getNumSession();
		void setLevel(const int&);
		const int& getLevel();
		void setRTS(JoueurRTS* rts){m_rts=rts;};
		const JoueurRTS* getRTS(){return m_rts;};
		void setRPG(JoueurRPG* rpg){m_rpg=rpg;};
		const JoueurRPG* getRPG(){return m_rpg;};
		void setTypeGamplay(const TypeGameplay t){m_type_gamplay=t;};
		const TypeGameplay getTypeGameplay(){return m_type_gamplay;};
		Equipe *equipe;
		int id;
    protected:
    private:
		std::string m_nom;
		std::string m_num_session;
		TypeGameplay m_type_gamplay;
		int m_level;
		JoueurRPG* m_rpg;
		JoueurRTS* m_rts;
};

#endif // JOUEUR_H
