#include "GlobalServer.h"

GlobalServer::GlobalServer()
{
    ip = "127.0.0.1";
    tcp = new TcpConnection();
}

GlobalServer::~GlobalServer()
{
    delete tcp;
}

void GlobalServer::startAccept()
{
    TcpConnection::pointer connect =
}

