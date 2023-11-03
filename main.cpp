#include <iostream>
#include "TCPServer.h"

int main() {
    using http::TcpServer;

    TcpServer server = TcpServer("0.0.0.0", 1234);
    server.startListen();

    return EXIT_SUCCESS;
}
