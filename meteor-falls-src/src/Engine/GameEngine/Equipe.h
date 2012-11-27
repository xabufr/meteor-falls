#ifndef EQUIPE_H
#define EQUIPE_H

class Faction;

class Equipe
{
    public:
        Equipe();
        virtual ~Equipe();

        Faction* faction();
        void setFaction(Faction*);
    protected:
    private:
        Faction *m_faction;
};

#endif // EQUIPE_H
