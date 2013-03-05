#ifndef JOUEUR_H
#define JOUEUR_H
#include <string>
#include <vector>

class Equipe;
class JoueurRTS;
class Avatar;
class Hero;
class JoueurRPG;
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
            RPG,
			NONE_GAMEPLAY
        };
        Joueur();
        virtual ~Joueur();
        virtual const Type getType(){return Type::NONE;};
		void setNom(const std::string&);
		const std::string& getNom();
		void setNumSession(const std::string&);
		const std::string& getNumSession();
		void setLevel(int);
		int getLevel() const;
		JoueurRTS* getRTS(){return m_rts;}
		JoueurRPG* getRPG(){return m_rpg;}
		void setTypeGamplay(TypeGameplay t);
		const TypeGameplay getTypeGameplay(){return m_type_gamplay;}
		void changeTeam(Equipe*);
		Equipe* equipe() { return m_equipe; }
		const std::vector<Avatar*> avatars() const;
		void addAvatar(Avatar*);
		void clearAvatars();
		Avatar* avatar(int) const;
		int id() const;
		void setId(int);
		long ping;
    private:
		void setRTS(JoueurRTS* rts){m_rts=rts;}
		void setRPG(JoueurRPG* rpg){m_rpg=rpg;}

		std::string m_nom;
		std::string m_num_session;
		TypeGameplay m_type_gamplay;
		int m_level;
		int m_id;
		JoueurRPG* m_rpg;
		JoueurRTS* m_rts;
		Equipe *m_equipe;

		std::vector<Avatar*> m_avatars;
};

#endif // JOUEUR_H
