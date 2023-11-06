#include "HttpRequest.h"

#include <sstream>

const char LINE_END = '\n';
const std::string END_OF_HEADERS = "\r";

namespace http {

HttpRequest::HttpRequest(std::string raw_serialized_request) {

    std::istringstream ss(raw_serialized_request);

    /*std::string request_headers;
    std::string request_body;
    */

    // parse request line
    {
        std::string request_line;
        std::getline(ss, request_line, LINE_END);
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
            std::string key = header_line.substr(0,header_line.find(": "));
            std::string value = header_line.substr(header_line.find(": ")+2, header_line.length());
            headers_.insert({key, value});

            std::getline(ss, header_line, LINE_END);
        }
    }

    // TODO: tähän loput mitkä ei mennyt muihin
    content_body_ = raw_serialized_request;

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