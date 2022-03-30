#include "client.h"

#include <string>
#include <iostream>

extern std::pair<std::string, int> connection();
extern bool CLICommandChecker(const std::string&);

int main()
{	
	auto [IpAdress, port] = connection(); // struct binding C++17

	Client socket(IpAdress, port);

	std::string str;
	while (str != "disconnect")
	{
		std::cout << "$ ";
		std::getline(std::cin, str);

        if(!CLICommandChecker(str))
		{
            socket.sendAndRecv(str);
        }
		else if(str == "")
		{
			continue;
		}
		else if (str == "clear")
		{
			std::system("clear");
			continue;
		}
        else{
            std::cout << str<<": command not found" << std::endl;
        }

	}

	return 0;
}