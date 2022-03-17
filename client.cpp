#include "client.h"

#include <iostream>
#include <vector>

Socket_sender::Socket_sender(std::string IP_addres , int port)
{
	server_ip = IP_addres; // IPv4 address
	static const int SERVER_PORT = port ;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Error while creating socket\n";
		exit(1);
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);

	if (inet_pton(AF_INET, server_ip.c_str() , &server_addr.sin_addr) <= 0)
	{
		std::cerr << "inet_pton error\n";
		exit(1);
	}
	if (connect(sockfd, (SA *) &server_addr, sizeof(server_addr)) < 0)
	{
		std::cerr << "connect failed\n";
		exit(1);
	}
}

void Socket_sender::send_and_recv(const std::string& send_line)
{
	int n = 0;
	this->send_line = send_line;
	if (send(sockfd, send_line.c_str(), send_line.size(), 0) != send_line.size())
	{
		std::cerr << "write error\n";
		exit(1);
	}

	char ch;
	while ((n = recv(sockfd, &ch, 1, 0)))
	{
		if (ch == '\r') break;
		std::cout << ch ;
	}

	if (n < 0)
	{
		std::cerr << "read error\n";
		exit(1);
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

int main(int argc , char* argv[])
{
	if (argc < 3) 
	{
		std::cerr << "Invalid Argument" ;
	       	return 1;
	}
	std::string str;
	Socket_sender socket(argv[1], parsChar(argv[2]));

	while (true)
	{
		std::cout << "enter your command -> ";
		std::getline(std::cin, str);

		socket.send_and_recv(str);

		std::cout << std::endl;

		if ("disconnect" == str) break;
	}

	return 0;
}
