#ifndef AERIEN_H
#define AERIEN_H

#include "Mobile.h"

class Equipe;
class Aerien : public Mobile
{
    public:
        Aerien(Equipe*, TypeUnite* type, int id);
        virtual ~Aerien();
};

#endif // AERIEN_H
