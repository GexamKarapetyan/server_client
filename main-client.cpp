#include "client.h"

#include <string>
#include <iostream>

extern std::pair<std::string, int> connection();
extern bool CLICommandChecker(std::string command);

int main()
{	
	auto [IpAdress, port] = connection(); // struct binding C++17

	Client socket(IpAdress, port);

	std::string str;
	while (str != "disconnect")
	{
		std::cout << " -> ";
		std::getline(std::cin, str);

        if(!CLICommandChecker(str))
		{
            socket.sendAndRecv(str);
        }
        else{
            std::cout << "Wrong command" << std::endl;
        }

		std::cout << std::endl;
	}

	return 0;
}