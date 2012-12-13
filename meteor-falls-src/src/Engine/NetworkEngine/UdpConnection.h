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
    boost::asio::ip::udp::endpoint getConnectionEndpoint();

    virtual void startListen();

    virtual bool hasData();
    Data getData();

    virtual void send(std::string data);
    void send(std::string data, boost::asio::ip::udp::endpoint e);

    void bind(boost::asio::ip::udp::endpoint e);

    boost::asio::ip::udp::socket *socket(){return m_socket;}

    virtual ~UdpConnection();
protected:
    virtual void handleReadHeader(const boost::system::error_code&);
    virtual void handleReadData(const boost::system::error_code&);
    void handleSendData(std::string, boost::asio::ip::udp::endpoint);
    void handleSendData(std::string){}
    void handleStartReceive();

private:
    UdpConnection(boost::shared_ptr<boost::asio::io_service> service);

    boost::asio::ip::udp::endpoint m_endpointConnection, m_endpointSender;
    boost::asio::ip::udp::socket *m_socket;

    std::queue<std::pair<boost::asio::ip::udp::endpoint, std::string>> m_queue_buffers;

    boost::mutex m_mutex_buffers, m_mutex_connexion_endpoint;

    std::vector<char> m_buffer_receive;
    enum { header_size = 8 };
    char m_header_data[header_size];
};

#endif // UDPCONNECTION_H
