#ifndef ENGINE_H
#define ENGINE_H
#include "EngineType.h"

class EngineMessage;
class EngineManager;

class Engine
{
public:

    virtual void handleMessage(EngineMessage&) = 0;
    virtual void work() = 0;
    virtual EngineType getType() = 0;

    Engine(EngineManager *manager):m_manager(manager){};
    EngineManager* getManager(){return m_manager;};
protected:
    EngineManager *m_manager;
};

#endif // ENGINE_H
