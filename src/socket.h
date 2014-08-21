#ifndef SOCKET_HEADER
#define SOCKET_HEADER

#include <csdtio>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <errno.h>

#define BACKLOG 10

class Socket
{
public:
    Socket();
    ~Socket();
    bool create();
    bool bind(int);
    bool connect(int,int);
    bool listen();
    bool accept();
    int send(std::string);
    int recv(std::string&);

private:
    int sockfd; 
    int csockfd; //客户端
    int ssockfd; //服务端
    struct sockaddr_in cli_addr,serv_addr;
    bool is_valid();
};

#endif
