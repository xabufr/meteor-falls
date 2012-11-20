#ifndef GLOBALSERVER_H_INCLUDED
#define GLOBALSERVER_H_INCLUDED

#include "TcpConnection.h"
//#include "SslConnection.h"

class GlobalServer
{

    public:
        GlobalServer();
        ~GlobalServer();
        void startAccept();

    private:
        TcpConnection *tcp;
        //SslConnection *ssl;

};
#endif // GLOBALSERVER_H_INCLUDED
