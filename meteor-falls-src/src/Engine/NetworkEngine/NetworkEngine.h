#ifndef H_NETWORKENGINE_H
#define H_NETWORKENGINE_H
#include "Engine/Engine.h"

class NetworkEngine : public Engine
{
public:
    virtual void handleMessage(const EngineMessage&) = 0;
    virtual void work() = 0;
    virtual EngineType getType();
};

#endif // H_NETWORKENGINE_H
