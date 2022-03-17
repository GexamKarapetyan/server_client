#include <iostream>
#include <string>
#include <cstring>

#include "server.h"

Socket_reciver::Socket_reciver(std::string IP_addres , int port)
{
    static const int SERVER_PORT = port;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        std::cerr << "Error opening socket\n";
        std::exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP_addres.c_str()); // IPv4 address
    serv_addr.sin_port = htons(SERVER_PORT);

    if (bind(listenfd, (SA *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "ERROR on binding\n";
        exit(1);
    }

    std::cout << "server ip : " << inet_ntoa(serv_addr.sin_addr) << std::endl;
    if (listen(listenfd, 5) < 0)
        {
            std::cerr << "ERROR on listen\n";
            exit(1);
        }
}

void Socket_reciver::accept_clients()
{
    while (1)
    {
        socklen_t client_len = sizeof(cli_addr);
        connfd = (int*)malloc(sizeof(int));
        *connfd = accept(listenfd, (SA *)&cli_addr, &client_len);
        if (listen(listenfd, 5) < 0)
        {
            std::cerr << "ERROR on listen\n";
            exit(1);
        }
        pthread_create(&tid, NULL, server_thread_routine, (void*)connfd);
    }
}

int parsChar(const char* ch)
{
	int k{};
	while (*ch != '\0')
	{
		k = k * 10 + (*ch - '0');
		ch += 1;
	}
	return k;
}

int main(int argc , char*argv[])
{
    if(argc < 3){std::cerr << "Invalid Argument" ; return 1;}
    std::string IP_address = argv[1];
    Socket_reciver socket (IP_address, parsChar(argv[2]));
    socket.accept_clients();
    
    return 0;
}
