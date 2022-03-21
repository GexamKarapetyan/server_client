#include "server.h"
#include "helper.h"

#include <string>


int main()
{
    auto [IpAdress, port] = connection();
    Server socket (IpAdress, port);
    socket.acceptClients();
    
    return 0;
}