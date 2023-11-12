#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX

#include <exception>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "TCPSocket.h"
#include "HttpResponse.h"

namespace http {

using HandlerFunction = std::function<HttpResponse (HttpRequest, HttpResponse)>;

namespace {
    using ResourcePath = std::string;
    using HandlerContainer = std::unordered_map<ResourcePath, std::unordered_map<types::RequestMethod, HandlerFunction>>;
}

class TcpServer
{
public:
    TcpServer(std::string ip_address, int port);
    ~TcpServer();

    //
    void startListen();

    void bindHandler(types::RequestMethod request_method, ResourcePath resource_path, HandlerFunction handler);
    //template<class Func, typename... Ts>
    //void bindHandler(types::RequestMethod request_method, const std::string resource_path, Func handler, Ts... args);

    static HttpResponse buildTestResponse(std::string text = std::string());

private:
    std::string ip_address_;
    int port_;

    TCPSocket socket_;

     HandlerContainer handlers_;
};

} // namespace http
    
#endif
