#include "inc/TCPServer.h"

#include <sstream>
#include "inc/HttpRequest.h"
#include "inc/HttpResponse.h"
#include "inc/http_types.h"

namespace http {

const std::string NOT_FOUND_ERROR_HTML = "<!DOCTYPE html><html lang=\"en\"><body><h1> ERROR 404 Not Found </h1></body></html>";

TcpServer::TcpServer(std::string ip_address, int port)
    : ip_address_(ip_address), port_(port) {

    socket_.bindToAddress(ip_address_, port_);
}

TcpServer::~TcpServer() {

}

void TcpServer::startServing() {
    socket_.startListen();

    std::cout << "Listening on ADDRESS:  " << ip_address_
              << " PORT: " << port_ << std::endl;

    is_serving_ = true;

    while (is_serving_) {
        std::cout << "------  Waiting for new connection ------" <<  std::endl;

        TCPSocket connection_socket = socket_.acceptConnectionFromQueue();

        std::cout << "------ Received Request from client ------" << std::endl;

        HttpRequest req = connection_socket.readRequest();
        std::cout << getRequestMethodString(req.getRequestMethod()) << " " << req.getResourcePath()
                    << " " << types::getHttpProtocolVersionString(req.getProtocol()) << std::endl;
        std::cout << req.hasHeaderField(types::CONTENT_TYPE_HEADER) << std::endl;
        std::cout << types::getContentBodyFormatString(req.getContentBodyFormat()) << std::endl;

        HttpResponse response(types::HttpProtocolVersion::Unknown, types::ResponseStatusCode::Unknown);
        if(handlers_.find(req.getResourcePath()) != handlers_.end() && handlers_[req.getResourcePath()].find(req.getRequestMethod()) !=  handlers_[req.getResourcePath()].end()) {
            response = handlers_[req.getResourcePath()].at(req.getRequestMethod())(req, response);
        }
        else {
            response.setProtocol(types::HttpProtocolVersion::HTTP1_1);
            response.setResponseStatusCode(types::ResponseStatusCode::NotFound);
            response.setContentBodyFormat(types::ContentBodyFormat::text_html);
            response.setContentBody(NOT_FOUND_ERROR_HTML);
        }

        bool response_sent = connection_socket.sendResponse(response);
        if (response_sent) {
            std::cout << "------ Server Response sent to client ------"  << std::endl;
        }
        else {
            std::cout << "------ Error sending response to client ------" << std::endl;
        }
    }
}

void TcpServer::stopServing() {
    is_serving_ = false;
}


void TcpServer::bindHandler(types::RequestMethod request_method, ResourcePath resource_path,
                            HandlerFunction handler) {
    if(handlers_.find(resource_path) == handlers_.end()) {
        handlers_.insert({resource_path, {}});
    }

    handlers_[resource_path].insert({request_method, handler});
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

HttpResponse TcpServer::buildTestResponse(std::string text)  {
    std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p><p><b>MORO!<b></p><form method=\"get\" action=\"/start\">\n"
                           "    <h5>" "server message:  " + text + "</h5>\n"
                           "    <input type=\"submit\" value=\"Start\">\n"
                           "</form>"
                           "<form action=\"http://localhost:1234/\" method=\"post\" enctype=\"multipart/form-data\">\n"
                                                                   "  <label>Name: <input name=\"myTextField\" value=\"Test\"></label>\n"
                                                                   "  <label><input type=\"checkbox\" name=\"myCheckBox\"> Check</label>\n"
                                                                   "  <label>Upload file: <input type=\"file\" name=\"myFile\" value=\"test.txt\"></label>\n"
                                                                   "  <button>Send the file</button>\n"
                                                                   "</form></body></html>";
    HttpResponse response(types::HttpProtocolVersion::HTTP1_1,types::ResponseStatusCode::OK);
    response.setContentBodyFormat(types::ContentBodyFormat::text_html);
    response.setContentBody(htmlFile);


    return response;
}

} // namespace http
