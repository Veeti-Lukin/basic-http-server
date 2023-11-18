#include <iostream>
#include "http_server/TCPServer.h"
#include "http_server/http_types.h"
#include "http_server/HttpRequest.h"
#include "http_server/HttpResponse.h"

int main() {
    using http::TcpServer;

    TcpServer server = TcpServer("0.0.0.0", 2234);
    server.bindHandler(http::types::RequestMethod::GET, "/", [](http::HttpRequest a, http::HttpResponse b){
        std::string server_message = "";
        //std::getline(std::cin, server_message);
        return TcpServer::buildTestResponse(server_message);});

    server.bindHandler(http::types::RequestMethod::GET, "/start?", [](http::HttpRequest a, http::HttpResponse b){
        std::string html = "<!DOCTYPE html><html lang=\"en\"><body><h1> HANDLER IS WORKING!!! </h1></body></html>";

        http::HttpResponse response(http::types::HttpProtocolVersion::HTTP1_1, http::types::ResponseStatusCode::OK);
        response.setContentBodyFormat(http::types::ContentBodyFormat::text_html);
        response.setContentBody(html);

        return response;
    });
    server.startServing();

    return EXIT_SUCCESS;
}
