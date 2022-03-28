#include "server.h"

#include <string>

extern std::pair<std::string, int> connection();

int main()
{
    auto [IpAdress, port] = connection();
    Server socket (IpAdress, port);
    socket.acceptClients();
    
    return 0;
}