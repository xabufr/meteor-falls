#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "precompiled/asio.h"
#include "precompiled/shared_ptr.h"
#include "Connection.h"

class TcpConnection : public Connection, public boost::enable_shared_from_this<TcpConnection>
{
public:
    typedef boost::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::shared_ptr<boost::asio::io_service>);
    void send(std::string data);
    void startListen();
    void connect(boost::asio::ip::tcp::endpoint e);

    bool hasData();
    std::string getData();

    boost::asio::ip::tcp::socket& socket();

    ~TcpConnection();

protected:
    void handleReadHeader(const boost::system::error_code&);
    void handleReadData(const boost::system::error_code&);
    void handleSendData(std::string);

    void handleConnect(const boost::system::error_code&);

private:
    TcpConnection(boost::shared_ptr<boost::asio::io_service>);

    boost::asio::ip::tcp::socket *m_socket;
    boost::mutex m_mutex_buffer;
    std::queue<std::string> m_buffer_queue;

    enum { header_size = 8 };
    char m_header_data[header_size];
};

#endif // TCPCONNECTION_H
