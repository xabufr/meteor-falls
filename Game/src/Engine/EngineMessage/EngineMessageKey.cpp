#include "EngineMessageKey.h"
#include "../NetworkEngine/packet.h"


Packet &operator<<(Packet &packet, const mf::EngineMessageKey &key)
{
    packet << (std::uint8_t)key;
    return packet;
}


Packet &operator>>(Packet &packet, mf::EngineMessageKey &key)
{
    std::uint8_t value;
    packet >> value;
    key = (mf::EngineMessageKey) value;
    return packet;
}
