#include "http_tcpServer_linux.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>

namespace http {

const std::string SOCKET_INIT_ERROR = "Cannot create socket";
const std::string SOCKET_BIND_ERROR = "Cannot bind socket to address";
const std::string SOCKET_LISTENING_ERROR = "Failed to listen the socket";

const int BUFFER_SIZE = 30720;

TcpServer::TcpServer(std::string ip_address, int port)
    : ip_address_(ip_address), port_(port), socket_address_len_(sizeof (socket_address_)), server_message_(buildResponse()) {
    socket_address_.sin_family = AF_INET;
    socket_address_.sin_port = htons(port_);
    socket_address_.sin_addr.s_addr = inet_addr(ip_address_.c_str());

    startServer();
}

TcpServer::~TcpServer() {
    closeServer();
}

void TcpServer::startListen() {
    if (listen(socket_, max_connection_threads_)  < 0) {
        throw HTTP_SERVER_EXCEPTION(SOCKET_LISTENING_ERROR);
    }

    std::cout << "Listening on ADDRESS:  " << inet_ntoa(socket_address_.sin_addr)
              << " PORT: " << ntohs(socket_address_.sin_port) << std::endl;

    int received_bytes;

    while (true) {
        std::cout << "Waiting for new connection" <<  std::endl;
        acceptConnection(new_socket_);

        char buffer[BUFFER_SIZE] = {0};
        received_bytes = read(new_socket_, buffer, BUFFER_SIZE);
        if (received_bytes < 0)
        {
           throw HTTP_SERVER_EXCEPTION("Failed to read bytes from client socket connection");
        }

        std::cout << "------ Received Request from client ------" << std::endl;

        sendResponse();
        close(new_socket_);
    }
}

int TcpServer::startServer() {
    socket_  = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_ < 0) {
        throw HTTP_SERVER_EXCEPTION(SOCKET_INIT_ERROR);
        return 1;
    }

    if(bind(socket_, (sockaddr*)&socket_address_, socket_address_len_) < 0) {
        throw HTTP_SERVER_EXCEPTION(SOCKET_BIND_ERROR);
        return 2;
    }
    return 0;
}

void TcpServer::closeServer() {
    close(socket_);
    close(new_socket_);
}

void TcpServer::acceptConnection(int &new_socket)
{
    new_socket = accept(socket_, (sockaddr*)&socket_address_, &socket_address_len_);

    if(new_socket < 0) {
        // TODO: muuta excpetion classia ja korjaa throwiks
        std::cout << "Server failed to accept incoming connection from ADDRESS: "
                  << inet_ntoa(socket_address_.sin_addr) << "; PORT: "
                  << ntohs(socket_address_.sin_port) << std::endl;
    }

}

void TcpServer::sendResponse() {
    int bytes_sent;

    bytes_sent = write(new_socket_, server_message_.c_str(), server_message_.size());
    if (bytes_sent == server_message_.size()) {
        std::cout << "------ Server Response sent to client ------"  << std::endl;
    }
    else {
        std::cout << "Error sending response to client" << std::endl;
    }
}

std::string TcpServer::buildResponse() {
    std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p><p><b>MORO!<b></p></body></html>";
    std::ostringstream ss;
    ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
       << htmlFile;

    return ss.str();
}

} // namespace http
