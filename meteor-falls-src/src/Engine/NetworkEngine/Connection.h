#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/thread/mutex.hpp>
#include <boost/asio.hpp>
#include <queue>

class Connection
{
    public:
        Connection(boost::shared_ptr<boost::asio::io_service>);
        virtual ~Connection();

        bool hasError();
        boost::system::error_code getError();

        virtual void send(std::string data) = 0;
        virtual void startListen() = 0;

        virtual bool hasData() = 0;

        virtual bool isListening();
        virtual void setListening(bool);

        virtual bool isConnected();
        virtual void setConnected(bool);

    protected:
        virtual void m_addError(const boost::system::error_code&);

        virtual void handleReadHeader(const boost::system::error_code&) = 0;
        virtual void handleReadData(const boost::system::error_code&) = 0;
        virtual void handleSendData(std::string) = 0;
        virtual void handleDataSent(const boost::system::error_code&);

        std::vector<char> m_data_buffer;
        boost::shared_ptr<boost::asio::io_service> m_service;
    private:
        std::queue<boost::system::error_code> m_errors;
        boost::mutex m_mutexError, m_mutex_listening, m_mutex_connected;
        bool m_connected, m_listen;
};

#endif // CONNECTION_H
