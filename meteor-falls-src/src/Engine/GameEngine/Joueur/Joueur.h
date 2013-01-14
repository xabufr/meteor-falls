#ifndef JOUEUR_H
#define JOUEUR_H
#include <string>

class Equipe;
class Joueur
{
    public:
        enum Type{
            LAN,
            WAN,
            NONE
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
		Equipe *equipe;
		int id;
    protected:
    private:
		std::string m_nom;
		std::string m_num_session;
		int m_level;
};

#endif // JOUEUR_H
