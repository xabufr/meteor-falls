#ifndef RESSOURCES_H
#define RESSOURCES_H


struct Ressources
{
    int metal, wood, gold, population;
    Ressources();
    bool operator<=(const Ressources &other) const;
};

#endif // RESSOURCES_H
