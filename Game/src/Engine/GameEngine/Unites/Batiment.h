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
        void addBuildTask(Unite *builded, const TimeDuration &elapsed = TimeDuration());
        std::queue<std::pair<TimeDuration, Unite *> > buildStack() const;

    private:
        std::queue<std::pair<TimeDuration, Unite*>> m_buildTasks;
};

#endif // BATIMENT_H
