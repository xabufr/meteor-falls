#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <queue>

class UdpConnection : public boost::enable_shared_from_this<UdpConnection>
{
    typedef boost::shared_ptr<UdpConnection> pointer;
    public:
        static pointer create(boost::asio::io_service &s);

        void setEndpoint(boost::asio::ip::udp::endpoint &e);

        void send(std::string data);
        void send(std::string data, boost::asio::ip::udp::endpoint &e);

        void read_header(const boost::system::error_code& error);
        void read_data(const boost::system::error_code& error);

        void handleSend(const boost::system::error_code& error);

        void bind(boost::asio::ip::udp::endpoint &e);

        virtual ~UdpConnection();
    protected:
    private:
        UdpConnection(boost::asio::io_service &service);

        boost::asio::ip::udp::endpoint m_endpoint;
        boost::asio::ip::udp::socket m_socket;

        std::queue<std::string> m_queue_buffers;
        std::queue<boost::system::error_code> m_queue_errors;

        boost::mutex m_mutex_error, m_mutex_buffers;

        std::vector<char> m_buffer_receive;
        enum{ header_size = 8 };
        char m_header_data[header_size];
};

#endif // UDPCONNECTION_H
