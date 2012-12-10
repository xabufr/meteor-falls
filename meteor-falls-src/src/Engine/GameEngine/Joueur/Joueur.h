#ifndef JOUEUR_H
#define JOUEUR_H
#include <string>


class Joueur
{
    public:
        Joueur();
        virtual ~Joueur();
		void setNom(const std::string&);
		const std::string& getNom() const;
    protected:
    private:
		std::string m_nom;	
};

#endif // JOUEUR_H
