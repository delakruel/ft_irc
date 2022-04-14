#include "Server.hpp"


int     main(int argc, char **argv) {
    if (argc == 3) {
        Server  server();
        server.createConnection();
    }
    else {
        std::cout << "Wrong arguments for launching:\n";
        std::cout << "./ircserv <port> <password>\n";
        return (1);
    }
    return (0);
}