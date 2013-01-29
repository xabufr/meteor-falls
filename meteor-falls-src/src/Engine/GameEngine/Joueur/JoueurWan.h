#ifndef JOUEURWAN_H_INCLUDED
#define JOUEURWAN_H_INCLUDED

#include "Joueur.h"
class JoueurWan : public Joueur
{
    public:
        JoueurWan();
        ~JoueurWan();
        virtual const Type getType(){return Type::WAN;};
};

#endif // JOUEURWAN_H_INCLUDED
