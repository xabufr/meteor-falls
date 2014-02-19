#include "EngineMessageKey.h"
#include "../NetworkEngine/packet.h"


Packet &operator<<(Packet &packet, const EngineMessageKey &key)
{
    packet << (std::uint8_t)key;
    return packet;
}


Packet &operator>>(Packet &packet, EngineMessageKey &key)
{
    std::uint8_t value;
    packet >> value;
    key = (EngineMessageKey) value;
    return packet;
}
