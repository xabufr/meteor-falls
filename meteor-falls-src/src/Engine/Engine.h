
#include <iostream>

class EngineMessage;

class Engine
{
    public:

     virtual void handleMessage(const EngineMessage&) = 0;
     virtual void work() = 0;
     virtual void getType() = 0;

};

enum EngineType

{
    NetworkEngine = 0,
    GraphicEngine = 1,
    GameEngine = 2,
    SoundEngine = 3,
    PhysicalEngine = 4,
    ScriptEngine = 5,

};
