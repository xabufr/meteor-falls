#ifndef DEGAT_H
#define DEGAT_H

#include "typedefs.h"
#include <string>

class Degat
{
public:
    Degat(DegatId p_id,const std::string& p_nom);
    const DegatId id;
    const std::string nom;
};

#endif // DEGAT_H
