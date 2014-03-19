#ifndef BATIMENT_H
#define BATIMENT_H

#include "Unite.h"
#include <string>
#include <iostream>
#include <queue>
#include <Utils/timeduration.h>

class GameEngine;
class Equipe;
class Batiment: public Unite
{
    public:
        Batiment(Equipe*, TypeUnite* type, int id);

        void update(const TimeDuration &time);
        void addBuildTask(Unite *builded);

    private:
        std::queue<std::pair<TimeDuration, Unite*>> m_buildTasks;
};

#endif // BATIMENT_H
