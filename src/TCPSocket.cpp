
#include "http_server/TCPSocket.h"
#include "http_server/HttpServerException.h"


namespace http {

const std::string  WSA_STARTUP_ERROR = "WSAStartup failed";
const std::string SOCKET_INIT_ERROR = "Cannot create socket";
const std::string SOCKET_BIND_ERROR = "Cannot bind socket to address";
const std::string SOCKET_LISTENING_ERROR = "Failed to listen the socket";
const std::string SOCKET_CONNECTION_ACCEPT_ERROR = "Server failed to accept incoming connection from ADDRESS: *; PORT: *";
const std::string SOCKET_NOT_CONNECTED_TO_CLIENT_ERROR = "Socket not connected to client";

const int BUFFER_SIZE = 30720;

TCPSocket::TCPSocket() {
    #ifdef _WIN32
        if (WSAStartup(MAKEWORD(2, 0), &wsa_data_) != 0)
            throw HTTP_SERVER_EXCEPTION(WSA_STARTUP_ERROR);
    #endif

    socket_address_len_ = sizeof(socket_address_);
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0) {
        #ifdef __linux__
            throw HTTP_SERVER_EXCEPTION(SOCKET_INIT_ERROR);
        #elif _WIN32
            int err_num = WSAGetLastError();
            WSACleanup();
            throw HTTP_SERVER_EXCEPTION(SOCKET_INIT_ERROR + ". Socket function failed with error: *", {std::to_string(err_num)});
        #endif
    }
}

TCPSocket::~TCPSocket() {
    #ifdef __linux__
        close(socket_);
    #elif _WIN32
        closesocket(socket_);
        WSACleanup();
    #endif
}

void TCPSocket::bindToAddress(std::string& IP_address, int port) {
    socket_address_.sin_family = AF_INET;
    socket_address_.sin_port = htons(port);
    socket_address_.sin_addr.s_addr = inet_addr(IP_address.c_str());

    //  allows program to rebind to the given port, even if there is an unbound socket from a previous program run
    const char enable = 1;
    setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));


    #ifdef __linux__
        if (bind(socket_, (sockaddr*)&socket_address_, socket_address_len_) < 0) {
            throw HTTP_SERVER_EXCEPTION(SOCKET_BIND_ERROR);
    #elif _WIN32
        if (bind(socket_, (sockaddr*)&socket_address_, socket_address_len_) == SOCKET_ERROR) {
            int err_num = WSAGetLastError();
            closesocket(socket_);
            WSACleanup();
            throw HTTP_SERVER_EXCEPTION(SOCKET_BIND_ERROR + ". Bind failed with error *", {std::to_string(err_num)});
    #endif
    }

}

void TCPSocket::startListen() {
    if(listen(socket_, max_amount_of_connection_threads_) < 0)
        throw HTTP_SERVER_EXCEPTION(SOCKET_LISTENING_ERROR);
}

void TCPSocket::setMaxAmountOfConnectionThreads(unsigned int amount) {
    max_amount_of_connection_threads_ = amount;
}

TCPSocket TCPSocket::acceptConnectionFromQueue() {
    #ifdef __linux__
        int new_connection_socket;
    #elif _WIN32
        SOCKET new_connection_socket;
    #endif

    new_connection_socket = accept(socket_, (sockaddr*)&socket_address_, &socket_address_len_);
    if (new_connection_socket < 0)
        throw HTTP_SERVER_EXCEPTION(SOCKET_CONNECTION_ACCEPT_ERROR, {inet_ntoa(socket_address_.sin_addr),  std::to_string(ntohs(socket_address_.sin_port))});

    return TCPSocket(new_connection_socket);
}
std::string TCPSocket::readRawRequest() {
    if(!is_connected_to_client) throw HTTP_SERVER_EXCEPTION(SOCKET_NOT_CONNECTED_TO_CLIENT_ERROR);

    char buffer[BUFFER_SIZE] = {0};
    int received_bytes;

    #ifdef __linux__
        received_bytes = read(socket_, buffer, BUFFER_SIZE);
    #elif _WIN32
        received_bytes = recv(socket_, buffer, BUFFER_SIZE, 0);
    #endif
    if (received_bytes < 0) throw HTTP_SERVER_EXCEPTION("Failed to read bytes from client socket connection");
    return std::string(buffer);
}

HttpRequest TCPSocket::readRequest() {
    return HttpRequest(readRawRequest());
}

bool TCPSocket::sendRawResponse(std::string serialized_response) {
    if(!is_connected_to_client) throw HTTP_SERVER_EXCEPTION(SOCKET_NOT_CONNECTED_TO_CLIENT_ERROR);

    long bytes_sent = 0;
    long total_bytes_sent = 0;

    // this while loop handles the case where the message does not fit fully in to the kernels write buffer
    // if while loop runs more than once the message is continued from where the last message left
    while (total_bytes_sent < serialized_response.size()) {

        std::string serialized_response_split = serialized_response.substr(bytes_sent, serialized_response.size());

        #ifdef __linux__
            bytes_sent = write(socket_, serialized_response_split.c_str(), serialized_response.size());
        #elif _WIN32
            bytes_sent = send(socket_, serialized_response_split.c_str(), serialized_response.size(), 0);
        #endif
        // error occurred. Client might be disconnected
        if(bytes_sent < 0) break;

        total_bytes_sent += bytes_sent;
    }

    return total_bytes_sent == serialized_response.size();
}

bool TCPSocket::sendResponse(HttpResponse response) {
    return sendRawResponse(response.serialize());
}

#ifdef __linux__
    TCPSocket::TCPSocket(int sock) {
        socket_ = sock;
        is_connected_to_client = true;
    }
#elif _WIN32
    TCPSocket::TCPSocket(SOCKET sock) {
        if (WSAStartup(MAKEWORD(2, 0), &wsa_data_) != 0)
            throw HTTP_SERVER_EXCEPTION(WSA_STARTUP_ERROR);
        socket_ = sock;
        is_connected_to_client = true;
    }
#endif

} // http