#ifndef HTTPPROXY_HEADER
#define HTTPPROXY_HEADER

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>

class HTTPProxy
{
public:
    HTTPProxy(int);
    ~HTTPProxy();
    void epoll_control();    


private:

};

#endif
