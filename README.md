I have provided server-client connection by ipv4 protocol.
It's capable to accept up to 5 clients simultaneously.
Server have a command handler which can recieve commands from client and respond.
We have 2 commands - disconnect and get_time.
Client part has command line interface.
Supported commands are connect, disconnect and get_time.

g++ server.cpp -o server -lpthread && ./server

g++ client.cpp -o client -lpthread && ./client
