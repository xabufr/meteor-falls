#ifndef TERRESTRE_H
#define TERRESTRE_H

#include "Mobile.h"

class Equipe;
class Terrestre: public Mobile
{
    public:
        Terrestre(Equipe*, TypeUnite* type, int id);
        virtual ~Terrestre();
};

#endif // TERRESTRE_H
