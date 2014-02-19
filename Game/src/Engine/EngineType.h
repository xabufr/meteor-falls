#ifndef ENGINETYPE_H_INCLUDED
#define ENGINETYPE_H_INCLUDED

enum EngineType
{
    NetworkEngineType = 0,
    GraphicEngineType = 1,
    GameEngineType = 2,
    SoundEngineType = 3,
    PhysicalEngineType = 4,
    ScriptEngineType = 5,
    NoneEngineType = 6
};
class Packet;
Packet& operator<<(Packet& packet, const EngineType &t);
Packet& operator>>(Packet& packet, EngineType &t);

#endif // ENGINETYPE_H_INCLUDED
