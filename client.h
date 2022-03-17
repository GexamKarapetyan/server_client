#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstring>
#include <iostream>

typedef sockaddr SA;
const int MAXLINE = 255;

class Socket_sender
{
public:
    Socket_sender( std::string,int);
    void send_and_recv(const std::string&);
    ~Socket_sender() = default;
private:
    int sockfd;
    sockaddr_in server_addr;
    std::string server_ip;
    char recv_line[255];
    std::string send_line;
};


#endif // CLIENT_H
