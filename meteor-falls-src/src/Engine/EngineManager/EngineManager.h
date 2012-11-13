#ifndef ENGINEMANAGER_H
#define ENGINEMANAGER_H

#include <vector>
#include "../Engine.h"

class EngineManager
{
    public:
        std::vector<Engine*> engines;
        Engine* get(EngineType p_engine_type);

    protected:

    private:
};

#endif // ENGINEMANAGER_H
