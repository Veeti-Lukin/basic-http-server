#include <iostream>
#include "TCPServer_linux.h"

int main() {
    using http::TcpServer;

    TcpServer server = TcpServer("0.0.0.0", 8080);
    server.startListen();

    return EXIT_SUCCESS;
}
