#ifndef SSLCONNECTION_H
#define SSLCONNECTION_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "Connection.h"

class SslConnection: public boost::enable_shared_from_this<SslConnection>, public Connection
{
    public:
        enum Type{
            SERVER,
            CLIENT
        };
        typedef boost::shared_ptr<SslConnection> pointer;

        static pointer create(boost::shared_ptr<boost::asio::io_service>, Type);
        void connect(boost::asio::ip::tcp::endpoint);

        void connectionAccepted(const boost::system::error_code& ); //Méthode appelée par le serveur

        virtual void send(std::string data);
        virtual void startListen();
        virtual bool hasData();
        std::string getData();

        virtual ~SslConnection();


    protected:
        virtual void handleReadHeader(const boost::system::error_code&);
        virtual void handleReadData(const boost::system::error_code&);
        virtual void handleSendData(std::string);

        void handleConnect(const boost::system::error_code&);
        void handleHandshake(const boost::system::error_code&);

    private:
        SslConnection(boost::shared_ptr<boost::asio::io_service>, Type, boost::asio::ssl::context&);
        Type m_type;
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> m_socket;
        std::queue<std::string> m_dataQueue;
        boost::mutex m_mutex_data;

        enum {header_size=8};
        char m_header_data[header_size];

};

#endif // SSLCONNECTION_H
