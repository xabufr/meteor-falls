#ifndef MOBILE_H
#define MOBILE_H

#include "Unite.h"

class Equipe;
class Mobile : public Unite
{
    public:
        Mobile(Equipe*, TypeUnite* type, int id);
        virtual ~Mobile();
};

#endif // MOBILE_H
