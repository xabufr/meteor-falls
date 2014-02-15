#include "EngineType.h"
#include "NetworkEngine/packet.h"


Packet &operator<<(Packet &packet, const EngineType &t)
{
    packet << (std::uint8_t)t;
    return packet;
}


Packet &operator>>(Packet &packet, EngineType &t)
{
    std::uint8_t type;
    packet >> type;
    t = (EngineType) type;
    return packet;
}
