#include "httpproxy.h"

HTTPProxy::HTTPProxy(int port)
{
    std::cout << "HTTP Proxy Has Started!" << std::endl;
    ServerSocket server;
    if(!server.epoll_control(port))
    {
        exit(1);
    }    
    std::cout << "Listening on Port : "<<port << std::endl;
    


}
