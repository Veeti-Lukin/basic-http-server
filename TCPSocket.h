
#ifndef BASIC_HTTP_SERVER_TCPSOCKET_H
#define BASIC_HTTP_SERVER_TCPSOCKET_H

#ifdef __linux__
    #include <arpa/inet.h>
    #include <sys/socket.h>
#elif _WIN32
    #include <winsock.h>
#endif

#include <string>
#include <exception>
#include <unistd.h>
#include <vector>
#include "HttpRequest.h"
#include "HttpResponse.h"

namespace http {

/**
 * This class works as an hardware and platform abstraction layer that abstracts away underlying actual socket.
 * Works on both linux and windows by encapsulating platform specific "hardware" socket generation.
 */
class TCPSocket {
public:
    TCPSocket();
    ~TCPSocket();

    void bindToAddress(std::string& IP_address, int port);
    // moves socket to passive listen mode where it listens for incoming connections on our socket address.
    // new connections are put in the connetion thread queue
    void startListen();
    //unsigned long getConnectionQueueLen();
    // accepts a connection from the queue
    TCPSocket acceptConnectionFromQueue();

    void setMaxAmountOfConnectionThreads(unsigned int amount);

    std::string readRawRequest();
    HttpRequest readRequest();
    bool sendRawResponse(std::string serialized_response);
    bool sendResponse(HttpResponse response);

private:
#ifdef __linux__
    int socket_;
    unsigned int socket_address_len_;
#elif _WIN32
    SOCKET socket_;
    WSAData wsa_data_;
    int socket_address_len_;
#endif
    sockaddr_in  socket_address_;

    // maximum number of connections threads the socket accepts to queue
    // if full the client connecting will be denied
    unsigned int max_amount_of_connection_threads_ = 1;
    bool is_connected_to_client = false;

    //Constructor that constructs a new socket with given underlying un-abstract socket
#ifdef __linux__
        TCPSocket(int sock);
#elif _WIN32
        TCPSocket(SOCKET sock);
#endif
};

} // http

#endif //BASIC_HTTP_SERVER_TCPSOCKET_H
