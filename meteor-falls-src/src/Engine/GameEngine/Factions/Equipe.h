#ifndef EQUIPE_H
#define EQUIPE_H
#include <string>
#include <vector>

class Unite;
class Faction;
class TypeUnite;

class Equipe
{
    public:
        Equipe();
        virtual ~Equipe();

        Faction* faction();
        void setFaction(Faction*);
        void create_unit(Unite*);
        void destroy_unite(Unite*);


    protected:
    private:
        Faction *m_faction;
        std::vector <TypeUnite*> m_batiments_cache;
        std::vector <Unite*> m_unites_construites;
};

#endif // EQUIPE_H
