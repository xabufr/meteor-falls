#ifndef EQUIPE_H
#define EQUIPE_H
#include <string>
#include <vector>

class Unite;
class Faction;
class TypeUnite;
class JoueurRPG;
class JoueurRTS;
class Joueur;
class UniteFactory;
class GameEngine;
class Equipe
{
    public:
        Equipe(GameEngine*, char id);
        virtual ~Equipe();

        Faction* faction();
        void setFaction(Faction*);
        void addUnit(Unite*);
        void removeUnit(Unite*);
        const std::vector<Unite*>& unites() const;

        void setJoueurRTS(JoueurRTS*);
        const std::vector<JoueurRPG*> getRPG() const;
        JoueurRTS* getRTS() const;
        char id() const;

        void addRPG(JoueurRPG*);
        void removeRPG(JoueurRPG*);

        void addJoueur(Joueur*);
        void removeJoueur(Joueur*);
        const std::vector<Joueur*> joueurs() const;

        UniteFactory* factory() const;
        void setFactory(UniteFactory*);

        Unite* getUnite(int) const;
        GameEngine* game() const;

        void update(float seconds);

    protected:
    private:
        Faction *m_faction;
        std::vector <const TypeUnite*> m_batiments_cache;
        std::vector <Unite*> m_unites_construites;
        std::vector<JoueurRPG*> m_joueursRPS;
        JoueurRTS *m_joueurRTS;
        std::vector<Joueur*> m_joueurs;
        char m_id;
        UniteFactory *m_factory;
        GameEngine *m_game;
};

#endif // EQUIPE_H
