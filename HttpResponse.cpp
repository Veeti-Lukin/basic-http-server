#include "HttpResponse.h"

#include "HttpServerException.h"


namespace http {

const std::string NOT_READY_FOR_SERIALIZATION_ERROR = "response not ready for serialization";

HttpResponse::HttpResponse(types::HttpProtocolVersion protocol_version, types::ResponseStatusCode status_code) {
    protocol_version_ = protocol_version;
    response_status_code_ = status_code;
}

void HttpResponse::setProtocol(types::HttpProtocolVersion protocol_version) {
    protocol_version_ = protocol_version;
}

void HttpResponse::setResponseStatusCode(types::ResponseStatusCode status_code) {
    response_status_code_ = status_code;
}

void HttpResponse::addHeader(std::string key, std::string value) {
    headers_[key] = value;
}

void HttpResponse::setContentBodyFormat(types::ContentBodyFormat content_body_format) {
    content_body_format_ = content_body_format;
}

void HttpResponse::setContentBody(std::string serialized_content_body) {
    content_body_ = serialized_content_body;
}

bool HttpResponse::isReadyForSerialization() {
    if(response_status_code_ == types::ResponseStatusCode::Unknown) return false;
    if(protocol_version_ == types::HttpProtocolVersion::Unknown) return false;
    if(!content_body_.empty() && content_body_format_ == types::ContentBodyFormat::Unknown) return false;
    return true;
}

std::string HttpResponse::serialize() {
    if(!isReadyForSerialization()) throw HTTP_SERVER_EXCEPTION(NOT_READY_FOR_SERIALIZATION_ERROR);

    std::ostringstream ss;
    // add response line
    ss << types::getHttpProtocolVersionString(protocol_version_) << " "
        << types::getResponseStatusCodeString(response_status_code_);

    // Add Headers
    ss << "\n" <<"Server: basic-http-server by Konna";
    for (auto& kv_pair : headers_) {
        ss << "\n" << kv_pair.first << ": " << kv_pair.second;
    }

    if (!content_body_.empty()) {
        ss << "\n";
        ss << types::CONTENT_TYPE_HEADER << ": " << types::getContentBodyFormatString(content_body_format_) << "\n";
        ss << types::CONTENT_LENGTH_HEADER << ": " << content_body_.size();
    }

    ss << types::END_OF_HEADERS;

    //add body
    ss << content_body_;

    return ss.str();
}

} // http