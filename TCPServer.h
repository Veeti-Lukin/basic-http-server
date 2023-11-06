#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX

#include <exception>
#include <string>
#include <iostream>
#include <vector>
#include "TCPSocket.h"
#include "HttpResponse.h"

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

    HttpResponse buildTestResponse(std::string text = std::string());
};

} // namespace http
    
#endif
