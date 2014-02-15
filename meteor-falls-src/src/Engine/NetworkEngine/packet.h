#ifndef PACKET_H
#define PACKET_H
#include <vector>
#include <cstdint>
#include <string>
#include <cstring>
#include <map>
#include <boost/asio/ip/address.hpp>

class Packet
{
public:
    Packet();
    Packet(const std::vector<char> data);

    void setData(const std::vector<char> data);

    Packet &operator<<(bool data);
    Packet &operator<<(std::int8_t data);
    Packet &operator<<(std::uint8_t data);
    Packet &operator<<(std::int16_t data);
    Packet &operator<<(std::uint16_t data);
    Packet &operator<<(std::int32_t data);
    Packet &operator<<(std::uint32_t data);
    Packet &operator<<(float data);
    Packet &operator<<(double data);
    Packet &operator<<(const std::string& data);
    template<typename T>
    Packet &operator<<(const std::vector<T> &data);
    template<typename K, typename V>
    Packet &operator <<(const std::map<K, V> &data);

    Packet &operator>>(bool &data);
    Packet &operator>>(std::int8_t &data);
    Packet &operator>>(std::uint8_t &data);
    Packet &operator>>(std::int16_t &data);
    Packet &operator>>(std::uint16_t &data);
    Packet &operator>>(std::int32_t &data);
    Packet &operator>>(std::uint32_t &data);
    Packet &operator>>(float &data);
    Packet &operator>>(double &data);
    Packet &operator>>(std::string &data);
    template<typename T>
    Packet &operator>>(std::vector<T> &data);
    template<typename K, typename V>
    Packet &operator >>(std::map<K, V> &data);

    const std::vector<char>& getData() const;

    boost::asio::ip::address sender;

private:
    template<typename T>
    T read();

    std::vector<char> m_data;
    std::size_t m_readPos;

    void append(const void* data, std::size_t sizeInByte);
};

template<typename K, typename V>
Packet &Packet::operator >>(std::map<K, V> &data)
{
    data.clear();
    std::uint32_t size, i;
    *this >> size;
    for(i=0;i<size;++i) {
        K key;
        V value;
        *this >> key >> value;
        data[key] = value;
    }
    return *this;
}

template<typename K, typename V>
Packet &Packet::operator <<(const std::map<K, V> &data)
{
    std::uint32_t size = data.size();
    *this << size;
    for(auto &entry : data) {
        *this << entry.first << entry.second;
    }
    return *this;
}

template<typename T>
Packet &Packet::operator>>(std::vector<T> &data)
{
    data.clear();
    std::uint32_t size, i;
    *this >> size;
    data.resize(size);
    for(i=0;i<size;++i) {
        T value;
        *this >> value;
        data[i] = value;
    }
    return *this;
}

template<typename T>
Packet &Packet::operator<<(const std::vector<T> &data)
{
    std::uint32_t size = data.size();
    *this << size;
    for(const T &value : data) {
        *this << value;
    }
    return *this;
}

template<typename T>
T Packet::read()
{
    T retValue = *reinterpret_cast<const T*>(&m_data[m_readPos]);
    m_readPos += sizeof(retValue);
    return retValue;
}

#endif // PACKET_H
