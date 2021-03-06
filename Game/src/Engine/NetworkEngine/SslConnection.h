#ifndef SSLCONNECTION_H
#define SSLCONNECTION_H

#include "../../precompiled/asio.h"
#include "../../precompiled/shared_ptr.h"
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
        void connect(boost::asio::ip::tcp::endpoint);//CONNECTION AU SERVER

        void connectionAccepted(); //Méthode appelée par le serveur
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::lowest_layer_type& socket();

        virtual void send(std::string data);
        virtual void send(const char *data, std::size_t size);
        virtual void startListen();
        virtual bool hasData();
        std::string getData();

        virtual ~SslConnection();
        static std::string getPass(){return "test";}
        static bool verify_certificate(bool preverified,
        boost::asio::ssl::verify_context& ctx){return true;}


    protected:
        virtual void handleReadHeader(const boost::system::error_code&);
        virtual void handleReadData(const boost::system::error_code&);
        virtual void handleSendData(std::string);
        virtual void handleSendData(const char *data, std::size_t size);

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
