#include "server.h"
#include "helper.h"

#include <string>
#include <cstring>

static void* serverThreadRoutine(void *arg)
    {
        int _connfd;
        int n;
        char getLine[MAXLINE];
        int pid;
        int recvLine_len;

        _connfd = *(int*)arg;
        pthread_detach(pthread_self());

        if (_connfd < 0)
        {
            std::cerr <<  "ERROR on listen";
            exit(1);
        }
        while (1)
        {
            bzero(getLine, MAXLINE);
            n = recv(_connfd, getLine, MAXLINE, 0);
            
            std::cout << getLine << std::endl;

            if (n < 0)
            {
                std::cerr <<  "ERROR on read";
                break;
            }

            std::string recvLine(getLine);

            if(recvLine.find(COMMANDS::HELP) < recvLine.size())
            {
                recvLine = CLICommandHelper();
            }
            else if(recvLine.find(COMMANDS::TIME) < recvLine.size()) {
                std::time_t result = std::time(nullptr);
                recvLine = std::asctime(std::localtime(&result));
            }
            else if(recvLine.find(COMMANDS::DISCONNECT) < recvLine.size())
            {
                recvLine = "thank you\n\r" ;
                send(_connfd, &recvLine[0], recvLine.size(), 0);
                break;
            }

            recvLine = recvLine + "\n\r";
            std::cout<< recvLine << std::endl;
            send(_connfd, recvLine.c_str(), recvLine.size(), 0);
        }

        close(_connfd);
        free(arg);
        return 0;
    }

Server::Server(std::string IP_addres , int port)
{
    static const int SERVER_PORT = port;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        std::cerr << "Error opening socket\n";
        std::exit(1);
    }

    bzero((char *) &servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(IP_addres.c_str()); // IPv4 address
    servAddr.sin_port = htons(SERVER_PORT);

    if (bind(listenfd, (sockaddr *) &servAddr, sizeof(servAddr)) < 0)
    {
        std::cerr << "ERROR on binding\n";
        exit(1);
    }

    std::cout << "server ip : " << inet_ntoa(servAddr.sin_addr) << std::endl;
    if (listen(listenfd, 5) < 0)
        {
            std::cerr << "ERROR on listen\n";
            exit(1);
        }
}

void Server::acceptClients()
{
    while (1)
    {
        socklen_t client_len = sizeof(cliAddr);
        connfd = (int*)malloc(sizeof(int));
        *connfd = accept(listenfd, (sockaddr *)&cliAddr, &client_len);
        if (listen(listenfd, 5) < 0)
        {
            std::cerr << "ERROR on listen\n";
            exit(1);
        }
        pthread_create(&tid, NULL, serverThreadRoutine, (void*)connfd);
    }
}