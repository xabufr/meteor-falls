#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <queue>

class TcpConnection : public boost::enable_shared_from_this<TcpConnection>
{
    public:
        typedef boost::shared_ptr<TcpConnection> pointer;
        static pointer create(boost::asio::io_service& service, boost::asio::ip::tcp::endpoint& endpoint);

        bool hasData();
        std::string getData();

        bool hasError();
        boost::system::error_code getError();

        void send(std::string data);

        virtual ~TcpConnection();
        void readHeader(const boost::system::error_code& error);
        void readData(const boost::system::error_code& error);
        void handleConnect(const boost::system::error_code& error);
        void handleWrite(const boost::system::error_code& error);
    protected:
    private:



        TcpConnection(boost::asio::io_service& service, boost::asio::ip::tcp::endpoint& endpoint);


        boost::asio::ip::tcp::socket *m_socket;
        std::vector<char> m_input_buffer;

        std::queue<std::string> m_queue_buffer;
        std::queue<boost::system::error_code> m_queue_error;

        boost::mutex m_mutex_buffer;
        boost::mutex m_mutex_error;
        enum{ m_header_size = 8 };
        char m_input_header_buffer[m_header_size];
};

#endif // TCPCONNECTION_H
