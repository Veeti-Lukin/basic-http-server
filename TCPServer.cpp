#include "TCPServer.h"

#include <unistd.h>
#include <sstream>

namespace http {

const int BUFFER_SIZE = 30720;

TcpServer::TcpServer(std::string ip_address, int port)
    : ip_address_(ip_address), port_(port), server_message_(buildResponse()) {

    socket_.bindToAddress(ip_address_, port_);
}

TcpServer::~TcpServer() {

}

void TcpServer::startListen() {
    socket_.startListen();

    std::cout << "Listening on ADDRESS:  " << ip_address_
              << " PORT: " << port_ << std::endl;

    while (true) {
        std::cout << "Waiting for new connection" <<  std::endl;

        TCPSocket connection_socket = socket_.acceptConnectionFromQueue();

        std::cout << "------ Received Request from client ------" << std::endl;
        std::cout << connection_socket.readRequest() << std::endl;

        //sendResponse();
        std::string a;
        //std::getline(std::cin, a);

        connection_socket.sendResponse(buildResponse(a));
    }
}


/*void TcpServer::sendResponse() {
    int bytes_sent;

    bytes_sent = write(new_socket_, server_message_.c_str(), server_message_.size());
    if (bytes_sent == server_message_.size()) {
        std::cout << "------ Server Response sent to client ------"  << std::endl;
    }
    else {
        std::cout << "Error sending response to client" << std::endl;
    }
}*/

std::string TcpServer::buildResponse(std::string text) {
    std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p><p><b>MORO!<b></p><form method=\"get\" action=\"/start\">\n"
                           "    <h5>"+ text + "</h5>\n"
                           "    <input type=\"submit\" value=\"Start\">\n"
                           "</form></body></html>";
    std::ostringstream ss;
    ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
       << htmlFile;

    return ss.str();
}

} // namespace http
