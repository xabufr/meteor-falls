#ifndef JOUEUR_H
#define JOUEUR_H
#include <string>


class Joueur
{
    public:
        Joueur();
        virtual ~Joueur();
        virtual const std::string& getType(){return "";};
		void setNom(const std::string&);
		const std::string& getNom();
		void setNumSession(const std::string&);
		const std::string& getNumSession();
		void setLevel(const int&);
		const int& getLevel();
    protected:
    private:
		std::string m_nom;
		std::string m_num_session;
		int m_level;
};

#endif // JOUEUR_H
