#include "http_proxy.h"

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " Port" << std::endl;
        return 1;
    }

    int port = atoi(argv[1]);
    HTTPProxy *proxy = new HTTPProxy(port);    

    return 0;
}
