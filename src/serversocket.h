#ifndef SERVERSOCKET_HEADER
#define SERVERSOCKET_HEADER

#include "socket.h"

class ServerSocket : public Socket
{
public:
    ServerSocket();
    ServerSocket(int);
    ~ServerSocket();
    bool accept();
    bool epoll_control(int port);
    void epoll_loop();
    void recv();
private:
    struct epoll_event ev,events[20];
    int epfd;
    int nfds;
    struct sockaddr_in cli_addr;
    int csockfd;
    char buffer[4096];
    char type[256];
    char url[1024];
    char proto[256];
};

#endif
