#include "socket.h"

Socket::Socket()
{
    memset(&cli_addr,0,sizeof(cli_addr));    
    sockfd = -1;
//    csockfd = -1;
//    ssockfd = -1;
}

Socket::~Socket()
{
    if(is_valid())
    {
        close(sockfd);
    }
}

bool Socket::is_valid()
{
    return sockfd != -1;
}

// creating the listening socket for our proxy server
bool Socket::create()
{
    bzero((char*)&cli_addr,sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(atoi(argv[1]));
    cli_addr.sin_addr.s_addr = INADDR_ANY;
    sockfd = socket(AF_INEF,SOCK_STREAM,0);
   
    if(!is_valid())
    {
        perror("failed to create socket!\n");        
        return false;
    }

    setnonblocking(sockfd);

    // 设置socket可重用
    int bReuse;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&bReuse,sizeof(int)) == -1)
    {
        perror("failed to set socket reused!\n");
        return false;
    }
    return true;
}

bool Socket::bind(int port)
{
    if(!is_valid())
    {
        return false;
    }
    
    if(::bind(sockfd,(struct sockaddr *)&cli_addr,sizeof(cli_addr)) == -1)
    {
        perror("failed to bind socket!\n");
        return false;
    }

    return true;
}

bool Socket::listen()
{
    if(!is_valid())
    {
        return false;
    }

    if(::listen(sockfd,BACKLOG) == -1)
    {
        perror("failed to listen socket!\n");
        return false;
    }
    return true;
}

// 返回listen文件描述符
int Socket::sockfd()
{
    return sockfd;
}

/*
int Socket::csockfd()
{
    return csockfd;
}
*/

