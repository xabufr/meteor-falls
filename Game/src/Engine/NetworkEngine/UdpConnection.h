#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include "../../precompiled/shared_ptr.h"
#include "Connection.h"
#include "../../precompiled/asio.h"

class UdpConnection : public Connection, public boost::enable_shared_from_this<UdpConnection>
{
public:
    typedef boost::shared_ptr<UdpConnection> pointer;
    typedef std::pair<boost::asio::ip::udp::endpoint, std::string> Data;

    static pointer create(boost::shared_ptr<boost::asio::io_service> s);

    void connect(boost::asio::ip::udp::endpoint e);
    const boost::asio::ip::udp::endpoint &getConnectionEndpoint();

    virtual void startListen();

    void send(const char *data, std::size_t size);
    void send(const char *data, std::size_t size, const boost::asio::ip::udp::endpoint &e);
    void send(const Packet &packet, const boost::asio::ip::udp::endpoint &e);

    void bind(boost::asio::ip::udp::endpoint e);

    boost::asio::ip::udp::socket *socket(){return m_socket;}

    virtual ~UdpConnection();
protected:
    virtual void handleReadData(const boost::system::error_code&);
    void handleSendData(boost::shared_ptr<char> data, std::size_t size, boost::asio::ip::udp::endpoint endpoint);
    void handleStartReceive();

private:
    UdpConnection(boost::shared_ptr<boost::asio::io_service> service);

    boost::asio::ip::udp::endpoint m_endpointConnection, m_endpointSender;
    boost::asio::ip::udp::socket *m_socket;

    boost::mutex m_mutex_connexion_endpoint;
};

#endif // UDPCONNECTION_H
