#include "client.h"
#include "helper.h"

#include <string>

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