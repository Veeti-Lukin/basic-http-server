#include "http_server/HttpRequest.h"

#include <sstream>
#include <regex>

const char LINE_END = '\n';
const std::string END_OF_HEADERS = "\r";

namespace http {

HttpRequest::HttpRequest(std::string raw_serialized_request) {

    std::istringstream ss(raw_serialized_request);

    // parse request line
    {
        std::string request_line;
        std::getline(ss, request_line, LINE_END);

        // remove the end of "\r" from the end of the line
        request_line = std::regex_replace(request_line, std::regex("\r"), "");

        std::istringstream request_line_ss(request_line);

        std::string request_method_string;
        std::getline(request_line_ss, request_method_string, ' ');
        request_method_ = types::getRequestMethodEnum(request_method_string);

        std::getline(request_line_ss, resource_path_, ' ');
        std::string protocol_string;
        std::getline(request_line_ss, protocol_string, ' ');

        protocol_ = types::getHttpProtocolVersionEnum(protocol_string);
    }

    // parse headers
    {
        std::string header_line;
        std::getline(ss, header_line, LINE_END);

        while (header_line != END_OF_HEADERS) {
            // remove the end of "\r" from the end of the line
            header_line = std::regex_replace(header_line, std::regex("\r"), "");

            std::string key = header_line.substr(0,header_line.find(": "));
            std::string value = header_line.substr(header_line.find(": ")+2, header_line.length());


            headers_.insert({key, value});

            std::getline(ss, header_line, LINE_END);
        }
    }

    // handle content body
    while (std::getline(ss, content_body_));

    if(hasHeaderField(types::CONTENT_TYPE_HEADER)) {
        content_body_format_ = types::getContentBodyFormatEnum(getHeaderField(types::CONTENT_TYPE_HEADER));
    }
    else {
        content_body_format_ = types::ContentBodyFormat::Unknown;
    }
}

types::RequestMethod HttpRequest::getRequestMethod() {
    return request_method_;
}

std::string HttpRequest::getResourcePath() {
    return resource_path_;
}

types::HttpProtocolVersion HttpRequest::getProtocol() {
    return protocol_;
}
bool HttpRequest::hasHeaderField(std::string& header_key) {
    return headers_.find(header_key) != headers_.end();
}

std::string HttpRequest::getHeaderField(std::string &header_key) {
    if(!hasHeaderField(header_key)) return "";

    return headers_.at(header_key);
}

std::string HttpRequest::getContentBody() {
    return content_body_;
}

types::ContentBodyFormat HttpRequest::getContentBodyFormat() {
    return content_body_format_;
}

} // http