
#ifndef BASIC_HTTP_SERVER_HTTPRESPONSE_H
#define BASIC_HTTP_SERVER_HTTPRESPONSE_H

#include <string>
#include <unordered_map>
#include "http_types.h"


namespace http {


class HttpResponse {
public:
    HttpResponse(types::HttpProtocolVersion protocol_version, types::ResponseStatusCode status_code);
    HttpResponse(types::HttpProtocolVersion protocol_version, types::ResponseStatusCode status_code,
                 types::ContentBodyFormat content_body_format, std::string content_body);

    void setProtocol(types::HttpProtocolVersion protocol_version);
    void setResponseStatusCode(types::ResponseStatusCode status_code);
    void addHeader(std::string key, std::string value);
    void setContentBodyFormat(types::ContentBodyFormat content_body_format);
    void setContentBody(std::string serialized_content_body);
    bool isReadyForSerialization();
    std::string serialize();

private:
    types::ResponseStatusCode response_status_code_ = types::ResponseStatusCode::Unknown;
    types::HttpProtocolVersion protocol_version_ = types::HttpProtocolVersion::HTTP1_1;
    std::unordered_map<std::string, std::string> headers_;
    types::ContentBodyFormat content_body_format_ = types::ContentBodyFormat::Unknown;
    std::string content_body_;
};


} // http

#endif //BASIC_HTTP_SERVER_HTTPRESPONSE_H
