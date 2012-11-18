#include "ServerNetworkEngine.h"
#include "clientnetworkengine.h"
#include "Engine/EngineMessage/EngineMessage.h"

#include <iostream>
#include <string>

int main()
{

    #ifdef CLIENT
        ClientNetworkEngine client(0);
        client.connect("127.0.0.1", 8888);
        while(1){
            client.work();
            std::string message;
            std::cin>>message;
            EngineMessage mes(0);
            mes.message=1;
            mes.strings[FILE_NAME] = message;
            client.sendToAllTcp(mes);
        }
    #else
        ServerNetworkEngine server(0,8888);
        while(1){
            boost::this_thread::sleep(boost::posix_time::milliseconds(10));
            server.work();
        }
    #endif // CLIENT

    return 0;
}
