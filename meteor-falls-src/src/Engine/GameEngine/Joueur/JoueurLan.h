#ifndef JOUEURLAN_H_INCLUDED
#define JOUEURLAN_H_INCLUDED

#include "Joueur.h"

class JoueurLan : public Joueur
{
    public:
        JoueurLan();
        ~JoueurLan();
        virtual const Type getType(){return Type::LAN;};
};

#endif // JOUEURLAN_H_INCLUDED
