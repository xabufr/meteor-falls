#ifndef CONNECTION_H
#define CONNECTION_H

#include "../../precompiled/asio.h"
#include "packet.h"
#include <queue>

class Connection
{
    public:
        Connection(boost::shared_ptr<boost::asio::io_service>);
        virtual ~Connection();

        bool hasError();
        boost::system::error_code getError();

        virtual void send(const char *data, std::size_t size) = 0;
        virtual void sendPacket(const Packet& packet);

        virtual void startListen() = 0;

        bool hasData();
        Packet nextPacket();
        void fillPacket(Packet &packet);

        virtual bool isListening();
        virtual void setListening(bool);

        virtual bool isConnected();
        virtual void setConnected(bool);

    protected:
        virtual void m_addError(const boost::system::error_code&);

        virtual void handleDataSent(const boost::system::error_code&);

        void addReceivedBuffer(const std::vector<char> &buffer);
        void addReceivedPacket(const Packet &packet);

        std::vector<char> m_data_buffer;
        boost::shared_ptr<boost::asio::io_service> m_service;
    private:
        std::queue<boost::system::error_code> m_errors;
        boost::mutex m_mutexError, m_mutex_listening, m_mutex_connected, m_mutex_received_buffers;
        bool m_connected, m_listen;
        std::queue<Packet> m_received_buffers;
};

#endif // CONNECTION_H
