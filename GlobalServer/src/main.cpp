#include "GlobalServer.h"
int main(int argc, char *argv[])
{
    GlobalServer *server = new GlobalServer(6050);

    while (server->get_start())
    {
        server->work();
    }

    delete server;
    return 0;
}
