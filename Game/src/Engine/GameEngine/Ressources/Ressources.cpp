#include "Ressources.h"


Ressources::Ressources(): metal(0), wood(0), gold(0), population(0)
{

}

bool Ressources::operator<=(const Ressources &other) const
{
    return metal <= other.metal &&
            wood <= other.wood &&
            gold <= other.gold;
}
