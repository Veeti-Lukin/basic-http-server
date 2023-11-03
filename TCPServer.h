#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX

#include <exception>
#include <string>
#include <iostream>
#include <vector>
#include "TCPSocket.h"

namespace http {    

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

    TCPSocket socket_;

    long incoming_message_;
    std::string server_message_;

    std::string buildResponse(std::string text = std::string());
};

} // namespace http
    
#endif
