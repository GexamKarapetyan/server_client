#include <iostream>
#include <string>
#include <cstring>

#include "server.h"

/* Creates the file descriptor */

Socket_reciver::Socket_reciver()
{
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        std::cerr << "Error opening socket\n";
        std::exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.11.217 "); // IPv4 address
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

/*
*this function listens query from provided port number ,
*creates file descriptor in a new thread and sends it to client.   
*/

void Socket_reciver::accept_clients()
{
    while (1)
    {
        socklen_t client_len = sizeof(cli_addr);
        connfd = (int*)malloc(sizeof(int));
        *connfd = accept(listenfd, (SA *)&cli_addr, &client_len);
        pthread_create(&tid, NULL, server_thread_routine, (void*)connfd);
    }
}



int main()
{
    Socket_reciver socket;
    socket.accept_clients();
    return 0;
}
