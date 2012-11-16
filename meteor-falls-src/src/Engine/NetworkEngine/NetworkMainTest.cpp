#include "ServerNetworkEngine.h"
#include "clientnetworkengine.h"
#include <iostream>
#include <string>

int main()
{

    #ifdef CLIENT
        ClientNetworkEngine client;
        client.connect("127.0.0.1", 8888);
        while(1){
            client.work();
            std::string message;
            std::cin>>message;
            client.send(message);
        }
    #else
        ServerNetworkEngine server(8888);
        while(1){
            boost::this_thread::sleep(boost::posix_time::milliseconds(10));
            server.work();
        }
    #endif // CLIENT

    return 0;
}
