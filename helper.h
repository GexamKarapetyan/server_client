#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <regex>


namespace COMMANDS
{
	const std::string HELP{"help"};
	const std::string TIME{"get_time"};
	const std::string DISCONNECT{"disconnect"};
}

std::regex regexIpAderes("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$");
std::regex regexPort("^([0-9]{3}|[0-9]{4}|[0-9]{5})$");


std::string CLICommandHelper()
{
    std::string str;
	str.reserve(100);
    str = "a. setup_conn <IP_ADDRESS> <PORT> (Where the “IP_ADDRESS” is IP Address of the Server and the “PORT” is Server Port Number)\n";
    str += "b. disconnect\n";
    str += "c. get_time\n";
    str += "d. help\n";
    str += "e. clear\n";
	return str;
}

bool CLICommandChecker(const std::string& command)
{
    if( command.find(COMMANDS::HELP) < command.size() 
					|| command.find(COMMANDS::TIME) < command.size() 
					|| command.find(COMMANDS::DISCONNECT) < command.size() )
    {
        return 0;
    }
    return 1;
}
std::pair<std::string, int> dataParser(std::string conception)
{
	std::stringstream stream(conception);
	std::string IpAdress;
	int port;

	stream >> IpAdress;
	if(IpAdress != "setup_conn")
	{
		std::cerr << "invalid command" << std::endl;
		exit(0);
	}
	stream >> IpAdress;
	if(!std::regex_match(IpAdress, regexIpAderes))  //address
	{
		std::cerr << "Wrong syntax of IP_ADDRESS"<< std::endl;
		exit(0);
	}
	stream >> port;
	if(!std::regex_match(std::to_string(port), regexPort))
	{
		std::cerr << "Wrong syntax of PORT" << std::endl;
		exit(0);
	}

	return std::make_pair(IpAdress, port);
}

std::pair<std::string, int> connection()
{
    std::string connectionData(COMMANDS::HELP);

	std::cout << "for connection enter ip_adress and port_number" << "(for help enter help) " << std::endl;
	while (connectionData == COMMANDS::HELP)
	{
		std::getline(std::cin, connectionData);
		if(connectionData == COMMANDS::HELP)
		{
			std::cout << CLICommandHelper();
		}
	}

	
	return dataParser(connectionData); // struct binding C++17
}

#endif //HELPER_H