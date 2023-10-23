#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX

#include <exception>
#include <string>
#include <iostream>
#include <arpa/inet.h>

namespace http {    

// Exception class, of which instances will be thrown in case of errors
// or faulty use of the server class
class HTTP_SERVER_EXCEPTION : public std::exception
{
public:
    HTTP_SERVER_EXCEPTION(const std::string& msg) :
        msg("Error: "+msg) {}

    virtual const char* what() const noexcept override
        {
            return msg.c_str();
        }
    private:
        std::string msg;
};



class TcpServer
{
public:
    TcpServer(std::string ip_address, int port);
    ~TcpServer();

    //
    void startListen();

private:
    std::string ip_address_;
    int port_;

    int socket_;
    int new_socket_;

    long incoming_message_;
    std::string server_message_;

    // defined in arpa/inet.h
    // TODO: make my own version of this
    struct sockaddr_in socket_address_;
    unsigned int socket_address_len_;

    // maximum number of coneections threads the socket accepts to queue
    // if full the client connecting will be denied
    unsigned int max_connection_threads_ = 1;

    int startServer();
    void closeServer();
    void acceptConnection(int &new_socket);
    void sendResponse();
    std::string buildResponse();
};

} // namespace http
    
#endif
