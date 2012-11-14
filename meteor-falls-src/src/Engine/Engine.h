#ifndef ENGINE_H
#define ENGINE_H

class EngineMessage;

enum EngineType

{
    NetworkEngine = 0,
    GraphicEngine = 1,
    GameEngine = 2,
    SoundEngine = 3,
    PhysicalEngine = 4,
    ScriptEngine = 5,

};

class Engine
{
    public:

     virtual void handleMessage(const EngineMessage&) = 0;
     virtual void work() = 0;
     virtual EngineType getType() = 0;

};

#endif // ENGINE_H
