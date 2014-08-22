#include "serversocket.h"

ServerSocket::ServerSocket()
{
    nfds = -1;
    csockfd = -1;
    epfd = epoll_create(256);
}

bool ServerSocket::epoll_control(int port)
{
    if(!Socket::create())
    {
        return false;
    }
   
    // 设置与要处理的事件相关的文件描述符
    ev.data.fd = Socket::sockfd();
    ev.events = EPOLLIN | EPOLLET;

    // 注册epoll事件
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);
 
    if(!Socket::bind(port))
    {
        return false;
    }

    if(!Socket::listen())
    {
        return false;
    }

    return true;
}

bool ServerSocket::accept()
{
    if(!is_valid())
    {
        return false;
    }

    int addr_size = sizeof(cli_addr);
    csockfd = ::accept(sockfd,(struct sockaddr *)&cli_addr,(socklen_t *) &addr_size);
    if(csockfd == -1)
    {
        perror("failed to accept!\n");
        return false;
    }
    setnonblocking(csockfd);

    return true;
}

bool ServerSocket::recv()
{
    bzero((char*)buffer,4096);
    // receiving the client http request
    recv(csockfd,buffer,4096,0);
    
    // 只关系http request的第一行，例如：
    // GET /index.html/ HTTP/1.1
    // type: GET
    // url: /index.html
    // proto： HTTP/1.1
    if(url[0] == '/')
    {
        strcpy(buffer,&url[1]);
        strcpy(url,buffer);
    }
    
    std::cout << "type、url、proto is "<< type << url << proto << std::endl;
    
    if((strncmp(type,"GET",3) ! = 0) || ((strncmp(proto,"HTTP/1.1",8) != 0) && (strncmp(proto,"HTTP/1.0",8) != 0)))
    {
        std::cout << "Bad Request format!" <<std::endl; 
        sprintf(buffer,"400 : Bad Request!");
        send(csockfd,buffer,strlen(buffer),0);
        return false;
    }

    return true;
}
void ServerSocket::epoll_loop()
{
    while(1)
    {
        int i;
        nfds = epoll_wait(epfd,events,20,0);
        for(i = 0; i < nfds; ++i)
        {
            //如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，则建立连接
            if(events[i].data.fd == sockfd)
            {
                if(!ServerSocket::accept())
                {
                    exit(-1);
                } 
                setnonblocking(csockfd);
                char *str = inet_ntoa(cli_addr.sin_addr);
                std::cout << "accept a connect from " << str << std::endl;
                ev.data.fd = csockfd;
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_ADD,csockfd,&ev);
            }
            // 如果是已连接的客户，并且收到数据，那么进行读入
            else if(events[i].events & EPOLLIN)
            {
            
            }
            else if(events[i].events & EPOLLOUT)
            {
            
            }

        }    
    }
}
