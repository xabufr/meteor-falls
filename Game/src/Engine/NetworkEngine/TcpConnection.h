#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "../../precompiled/asio.h"
#include "../../precompiled/shared_ptr.h"
#include "Connection.h"

class TcpConnection : public Connection, public boost::enable_shared_from_this<TcpConnection>
{
public:
    typedef boost::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::shared_ptr<boost::asio::io_service>);
    void send(const char *data, std::size_t size);
    void startListen();
    void connect(boost::asio::ip::tcp::endpoint e);

    void stop();

    boost::asio::ip::tcp::socket& socket();

    ~TcpConnection();

protected:
    void handleReadHeader(const boost::system::error_code&);
    void handleReadData(const boost::system::error_code&);
    void handleSendData(boost::shared_ptr<char> data, std::size_t size);

    void handleConnect(const boost::system::error_code&);

private:
    TcpConnection(boost::shared_ptr<boost::asio::io_service>);

    boost::asio::ip::tcp::socket *m_socket;

    std::uint8_t m_currentPacketSize;
};

#endif // TCPCONNECTION_H
