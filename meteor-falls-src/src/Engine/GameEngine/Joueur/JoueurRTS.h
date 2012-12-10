#ifndef JOUEURRTS_H
#define JOUEURRTS_H

class Joueur;
class JoueurRTS
{
    public:
        JoueurRTS(Joueur*);
        virtual ~JoueurRTS();
    protected:
    private:
		Joueur *m_joueur;
};

#endif // JOUEURRTS_H
