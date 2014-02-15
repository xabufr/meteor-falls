#include "packet.h"

#include <vector>
#include <arpa/inet.h>
#include <cstring>

Packet::Packet()
{
    m_readPos = 0;
}

Packet::Packet(const std::vector<char> data): m_data(data), m_readPos(0)
{

}

void Packet::setData(const std::vector<char> data)
{
    m_data = data;
    m_readPos = 0;
}

Packet &Packet::operator<<(bool data)
{
    *this << static_cast<std::int8_t>(data);
    return *this;
}

void Packet::append(const void *data, std::size_t sizeInByte)
{
    if(sizeInByte > 0) {
        std::size_t currentSize = m_data.size();
        m_data.resize(currentSize + sizeInByte);
        std::memcpy(&m_data[currentSize], data, sizeInByte);
    }
}

Packet &Packet::operator<<(std::int8_t data)
{
    append(&data, sizeof(data));
    return *this;
}

Packet &Packet::operator<<(std::uint8_t data)
{
    append(&data, sizeof(data));
    return *this;
}

Packet &Packet::operator<<(std::int16_t data)
{
    std::int16_t toWrite = htons(data);
    append(&toWrite, sizeof(toWrite));
    return *this;
}

Packet &Packet::operator<<(std::uint16_t data)
{
    std::uint16_t toWrite = htons(data);
    append(&toWrite, sizeof(toWrite));
    return *this;
}

Packet &Packet::operator<<(std::int32_t data)
{
    std::int32_t toWrite = htonl(data);
    append(&toWrite, sizeof(toWrite));
    return *this;
}

Packet &Packet::operator<<(std::uint32_t data)
{
    std::uint32_t toWrite = htonl(data);
    append(&toWrite, sizeof(toWrite));
    return *this;
}

Packet &Packet::operator<<(float data)
{
    append(&data, sizeof(data));
    return *this;
}

Packet &Packet::operator<<(double data)
{
    append(&data, sizeof(data));
    return *this;
}

Packet &Packet::operator<<(const std::string &data)
{
    std::uint32_t dataSize = data.size();
    *this << dataSize;
    if(dataSize > 0)
        append(data.c_str(), dataSize * sizeof(std::string::value_type));
    return *this;
}

Packet &Packet::operator>>(bool &data)
{
    std::int8_t value;
    *this >> value;
    data = value != 0;
    return *this;
}

Packet &Packet::operator>>(std::int8_t &data)
{
    data = read<std::int8_t>();
    return *this;
}

Packet &Packet::operator>>(std::uint8_t &data)
{
    data = read<std::uint8_t>();
    return *this;
}

Packet &Packet::operator>>(std::int16_t &data)
{
    data = read<std::int16_t>();
    data = ntohs(data);
    return *this;
}

Packet &Packet::operator>>(std::uint16_t &data)
{
    data = read<std::uint16_t>();
    data = ntohs(data);
    return *this;
}

Packet &Packet::operator>>(std::int32_t &data)
{
    data = read<std::int32_t>();
    data = ntohl(data);
    return *this;
}

Packet &Packet::operator>>(std::uint32_t &data)
{
    data = read<std::uint32_t>();
    data = ntohl(data);
    return *this;
}

Packet &Packet::operator>>(float &data)
{
    data = read<float>();
    return *this;
}

Packet &Packet::operator>>(double &data)
{
    data = read<double>();
    return *this;
}

Packet &Packet::operator>>(std::string &data)
{
    std::uint32_t length;
    *this >> length;
    if(length > 0) {
        data.assign(&m_data[m_readPos], length);
        m_readPos += length;
    }
    return *this;
}

const std::vector<char> &Packet::getData() const
{
    return m_data;
}
