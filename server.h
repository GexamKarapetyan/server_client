#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>

#include <sys/types.h>
#include <sys/wait.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#include <unistd.h>

const int  MAXLINE = 255;
typedef  sockaddr SA;

class Socket_reciver
{
public:
    Socket_reciver(std::string,int);
    void accept_clients();
private:
    int listenfd;
    int *connfd;
    sockaddr_in serv_addr;
    sockaddr_in cli_addr;
    pthread_t tid;

    static void* server_thread_routine(void *arg)
    {
        int _connfd;
        int n;
        char recv_line[MAXLINE];
        int pid;
        int recv_line_len;

        _connfd = *(int*)arg;
        pthread_detach(pthread_self());

        if (_connfd < 0)
        {
            std::cerr <<  "ERROR on listen";
            exit(1);
        }
        while (1)
        {
            bzero(recv_line, MAXLINE);
            n = recv(_connfd, recv_line, MAXLINE, 0);
            
            std::cout << recv_line << std::endl;

            if (n < 0)
            {
                std::cerr <<  "ERROR on read";
                break;
            }

            std::string recvLine(recv_line);
            
            if(recvLine == "get_time") {
                std::time_t result = std::time(nullptr);
                recvLine = std::asctime(std::localtime(&result));
            }

            if(recvLine == "disconnect")
            {
                recvLine = "thank you" ;
                send(_connfd, &recvLine[0], recvLine.size(), 0);
                break;
            }

            recvLine = recvLine + "\n\r";

            send(_connfd, &recvLine[0], recvLine.size(), 0);
        }

        close(_connfd);
        free(arg);
        return 0;
    }

};

#endif // SERVER_H
