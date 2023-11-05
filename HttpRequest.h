
#ifndef BASIC_HTTP_SERVER_HTTPREQUEST_H
#define BASIC_HTTP_SERVER_HTTPREQUEST_H

#include <string>
#include <unordered_map>
#include "http_types.h"

namespace http {

class HttpRequest {
public:
    explicit HttpRequest(std::string raw_serialized_request);

    types::RequestMethod getRequestMethod();
    std::string getResourcePath();
    std::string getProtocol();
    bool hasHeaderField(std::string& header_key);
    std::string getHeaderField(std::string& header_key);
    std::string getContentBody();
    types::ContentBodyFormat getContentBodyFormat();

private:
    types::RequestMethod request_method_;
    std::string resource_path_;
    std::string protocol_;
    std::string content_body_;
    std::unordered_map<std::string, std::string> headers_;
    types::ContentBodyFormat content_body_format_;
};

} // http

#endif //BASIC_HTTP_SERVER_HTTPREQUEST_H
