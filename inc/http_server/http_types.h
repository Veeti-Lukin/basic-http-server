#ifndef BASIC_HTTP_SERVER_HTTP_TYPES_H
#define BASIC_HTTP_SERVER_HTTP_TYPES_H

#include <string>
#include <iostream>
#include <regex>

namespace http {
namespace types {


// Status codes used for http response
// More information is found at: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
enum class ResponseStatusCode {
    // Informational responses (1xx)
    Continue = 100,
    SwitchingProtocols = 101,
    Processing = 102,
    EarlyHints = 103,

    // Successful responses (2xx)
    OK = 200,
    Created = 201,
    Accepted = 202,
    NonAuthoritativeInformation = 203,
    NoContent = 204,
    ResetContent = 205,
    PartialContent = 206,
    MultiStatus = 207,
    AlreadyReported = 208,
    IMUsed = 226,

    // Redirection messages (3xx)
    MultipleChoices = 300,
    MovedPermanently = 301,
    Found = 302,
    SeeOther = 303,
    NotModified = 304,
    UseProxy = 305,
    SwitchProxy = 306,
    TemporaryRedirect = 307,
    PermanentRedirect = 308,

    // Client errors (4xx)
    BadRequest = 400,
    Unauthorized = 401,
    PaymentRequired = 402,
    Forbidden = 403,
    NotFound = 404,
    MethodNotAllowed = 405,
    NotAcceptable = 406,
    ProxyAuthenticationRequired = 407,
    RequestTimeout = 408,
    Conflict = 409,
    Gone = 410,
    LengthRequired = 411,
    PreconditionFailed = 412,
    PayloadTooLarge = 413,
    URITooLong = 414,
    UnsupportedMediaType = 415,
    RangeNotSatisfiable = 416,
    ExpectationFailed = 417,
    IAmATeapot = 418,
    MisdirectedRequest = 421,
    UnprocessableEntity = 422,
    Locked = 423,
    FailedDependency = 424,
    TooEarly = 425,
    UpgradeRequired = 426,
    PreconditionRequired = 428,
    TooManyRequests = 429,
    RequestHeaderFieldsTooLarge = 431,
    UnavailableForLegalReasons = 451,

    // Server errors (5xx)
    InternalServerError = 500,
    NotImplemented = 501,
    BadGateway = 502,
    ServiceUnavailable = 503,
    GatewayTimeout = 504,
    HTTPVersionNotSupported = 505,
    VariantAlsoNegotiates = 506,
    InsufficientStorage = 507,
    LoopDetected = 508,
    NotExtended = 510,
    NetworkAuthenticationRequired = 511,

    Unknown = 999
};

inline std::string getResponseStatusCodeString(ResponseStatusCode status_code) {
    switch (status_code) {
        // Informational responses (1xx)
        case ResponseStatusCode::Continue:
            return "100 Continue";
        case ResponseStatusCode::SwitchingProtocols:
            return "101 Switching Protocols";
        case ResponseStatusCode::Processing:
            return "102 Processing";
        case ResponseStatusCode::EarlyHints:
            return "103 Early Hints";

            // Successful responses (2xx)
        case ResponseStatusCode::OK:
            return "200 OK";
        case ResponseStatusCode::Created:
            return "201 Created";
        case ResponseStatusCode::Accepted:
            return "202 Accepted";
        case ResponseStatusCode::NonAuthoritativeInformation:
            return "203 Non-Authoritative Information";
        case ResponseStatusCode::NoContent:
            return "204 No Content";
        case ResponseStatusCode::ResetContent:
            return "205 Reset Content";
        case ResponseStatusCode::PartialContent:
            return "206 Partial Content";
        case ResponseStatusCode::MultiStatus:
            return "207 Multi-Status";
        case ResponseStatusCode::AlreadyReported:
            return "208 Already Reported";
        case ResponseStatusCode::IMUsed:
            return "226 IM Used";

            // Redirection messages (3xx)
        case ResponseStatusCode::MultipleChoices:
            return "300 Multiple Choices";
        case ResponseStatusCode::MovedPermanently:
            return "301 Moved Permanently";
        case ResponseStatusCode::Found:
            return "302 Found";
        case ResponseStatusCode::SeeOther:
            return "303 See Other";
        case ResponseStatusCode::NotModified:
            return "304 Not Modified";
        case ResponseStatusCode::UseProxy:
            return "305 Use Proxy";
        case ResponseStatusCode::SwitchProxy:
            return "306 Switch Proxy";
        case ResponseStatusCode::TemporaryRedirect:
            return "307 Temporary Redirect";
        case ResponseStatusCode::PermanentRedirect:
            return "308 Permanent Redirect";

            // Client errors (4xx)
        case ResponseStatusCode::BadRequest:
            return "400 Bad Request";
        case ResponseStatusCode::Unauthorized:
            return "401 Unauthorized";
        case ResponseStatusCode::PaymentRequired:
            return "402 Payment Required";
        case ResponseStatusCode::Forbidden:
            return "403 Forbidden";
        case ResponseStatusCode::NotFound:
            return "404 Not Found";
        case ResponseStatusCode::MethodNotAllowed:
            return "405 Method Not Allowed";
        case ResponseStatusCode::NotAcceptable:
            return "406 Not Acceptable";
        case ResponseStatusCode::ProxyAuthenticationRequired:
            return "407 Proxy Authentication Required";
        case ResponseStatusCode::RequestTimeout:
            return "408 Request Timeout";
        case ResponseStatusCode::Conflict:
            return "409 Conflict";
        case ResponseStatusCode::Gone:
            return "410 Gone";
        case ResponseStatusCode::LengthRequired:
            return "411 Length Required";
        case ResponseStatusCode::PreconditionFailed:
            return "412 Precondition Failed";
        case ResponseStatusCode::PayloadTooLarge:
            return "413 Payload Too Large";
        case ResponseStatusCode::URITooLong:
            return "414 URI Too Long";
        case ResponseStatusCode::UnsupportedMediaType:
            return "415 Unsupported Media Type";
        case ResponseStatusCode::RangeNotSatisfiable:
            return "416 Range Not Satisfiable";
        case ResponseStatusCode::ExpectationFailed:
            return "417 Expectation Failed";
        case ResponseStatusCode::IAmATeapot:
            return "418 I'm a Teapot";
        case ResponseStatusCode::MisdirectedRequest:
            return "421 Misdirected Request";
        case ResponseStatusCode::UnprocessableEntity:
            return "422 Unprocessable Entity";
        case ResponseStatusCode::Locked:
            return "423 Locked";
        case ResponseStatusCode::FailedDependency:
            return "424 Failed Dependency";
        case ResponseStatusCode::TooEarly:
            return "425 Too Early";
        case ResponseStatusCode::UpgradeRequired:
            return "426 Upgrade Required";
        case ResponseStatusCode::PreconditionRequired:
            return "428 Precondition Required";
        case ResponseStatusCode::TooManyRequests:
            return "429 Too Many Requests";
        case ResponseStatusCode::RequestHeaderFieldsTooLarge:
            return "431 Request Header Fields Too Large";
        case ResponseStatusCode::UnavailableForLegalReasons:
            return "451 Unavailable For Legal Reasons";

            // Server errors (5xx)
        case ResponseStatusCode::InternalServerError:
            return "500 Internal Server Error";
        case ResponseStatusCode::NotImplemented:
            return "501 Not Implemented";
        case ResponseStatusCode::BadGateway:
            return "502 Bad Gateway";
        case ResponseStatusCode::ServiceUnavailable:
            return "503 Service Unavailable";
        case ResponseStatusCode::GatewayTimeout:
            return "504 Gateway Timeout";
        case ResponseStatusCode::HTTPVersionNotSupported:
            return "505 HTTP Version Not Supported";
        case ResponseStatusCode::VariantAlsoNegotiates:
            return "506 Variant Also Negotiates";
        case ResponseStatusCode::InsufficientStorage:
            return "507 Insufficient Storage";
        case ResponseStatusCode::LoopDetected:
            return "508 Loop Detected";
        case ResponseStatusCode::NotExtended:
            return "510 Not Extended";
        case ResponseStatusCode::NetworkAuthenticationRequired:
            return "511 Network Authentication Required";

        case ResponseStatusCode::Unknown:
        default:
            return "999 Unknown";
    }
}

inline ResponseStatusCode getResponseStatusCodeEnum(const std::string &statusString) {
    if (statusString == "100 Continue") return ResponseStatusCode::Continue;
    else if (statusString == "101 Switching Protocols") return ResponseStatusCode::SwitchingProtocols;
    else if (statusString == "102 Processing") return ResponseStatusCode::Processing;
    else if (statusString == "103 Early Hints") return ResponseStatusCode::EarlyHints;

        // Successful responses (2xx)
    else if (statusString == "200 OK") return ResponseStatusCode::OK;
    else if (statusString == "201 Created") return ResponseStatusCode::Created;
    else if (statusString == "202 Accepted") return ResponseStatusCode::Accepted;
    else if (statusString == "203 Non-Authoritative Information") return ResponseStatusCode::NonAuthoritativeInformation;
    else if (statusString == "204 No Content") return ResponseStatusCode::NoContent;
    else if (statusString == "205 Reset Content") return ResponseStatusCode::ResetContent;
    else if (statusString == "206 Partial Content") return ResponseStatusCode::PartialContent;
    else if (statusString == "207 Multi-Status") return ResponseStatusCode::MultiStatus;
    else if (statusString == "208 Already Reported") return ResponseStatusCode::AlreadyReported;
    else if (statusString == "226 IM Used") return ResponseStatusCode::IMUsed;

        // Redirection messages (3xx)
    else if (statusString == "300 Multiple Choices") return ResponseStatusCode::MultipleChoices;
    else if (statusString == "301 Moved Permanently") return ResponseStatusCode::MovedPermanently;
    else if (statusString == "302 Found") return ResponseStatusCode::Found;
    else if (statusString == "303 See Other") return ResponseStatusCode::SeeOther;
    else if (statusString == "304 Not Modified") return ResponseStatusCode::NotModified;
    else if (statusString == "305 Use Proxy") return ResponseStatusCode::UseProxy;
    else if (statusString == "306 Switch Proxy") return ResponseStatusCode::SwitchProxy;
    else if (statusString == "307 Temporary Redirect") return ResponseStatusCode::TemporaryRedirect;
    else if (statusString == "308 Permanent Redirect") return ResponseStatusCode::PermanentRedirect;

        // Client errors (4xx)
    else if (statusString == "400 Bad Request") return ResponseStatusCode::BadRequest;
    else if (statusString == "401 Unauthorized") return ResponseStatusCode::Unauthorized;
    else if (statusString == "402 Payment Required") return ResponseStatusCode::PaymentRequired;
    else if (statusString == "403 Forbidden") return ResponseStatusCode::Forbidden;
    else if (statusString == "404 Not Found") return ResponseStatusCode::NotFound;
    else if (statusString == "405 Method Not Allowed") return ResponseStatusCode::MethodNotAllowed;
    else if (statusString == "406 Not Acceptable") return ResponseStatusCode::NotAcceptable;
    else if (statusString == "407 Proxy Authentication Required") return ResponseStatusCode::ProxyAuthenticationRequired;
    else if (statusString == "408 Request Timeout") return ResponseStatusCode::RequestTimeout;
    else if (statusString == "409 Conflict") return ResponseStatusCode::Conflict;
    else if (statusString == "410 Gone") return ResponseStatusCode::Gone;
    else if (statusString == "411 Length Required") return ResponseStatusCode::LengthRequired;
    else if (statusString == "412 Precondition Failed") return ResponseStatusCode::PreconditionFailed;
    else if (statusString == "413 Payload Too Large") return ResponseStatusCode::PayloadTooLarge;
    else if (statusString == "414 URI Too Long") return ResponseStatusCode::URITooLong;
    else if (statusString == "415 Unsupported Media Type") return ResponseStatusCode::UnsupportedMediaType;
    else if (statusString == "416 Range Not Satisfiable") return ResponseStatusCode::RangeNotSatisfiable;
    else if (statusString == "417 Expectation Failed") return ResponseStatusCode::ExpectationFailed;
    else if (statusString == "418 I'm a Teapot") return ResponseStatusCode::IAmATeapot;
    else if (statusString == "421 Misdirected Request") return ResponseStatusCode::MisdirectedRequest;
    else if (statusString == "422 Unprocessable Entity") return ResponseStatusCode::UnprocessableEntity;
    else if (statusString == "423 Locked") return ResponseStatusCode::Locked;
    else if (statusString == "424 Failed Dependency") return ResponseStatusCode::FailedDependency;
    else if (statusString == "425 Too Early") return ResponseStatusCode::TooEarly;
    else if (statusString == "426 Upgrade Required") return ResponseStatusCode::UpgradeRequired;
    else if (statusString == "428 Precondition Required") return ResponseStatusCode::PreconditionRequired;
    else if (statusString == "429 Too Many Requests") return ResponseStatusCode::TooManyRequests;
    else if (statusString == "431 Request Header Fields Too Large") return ResponseStatusCode::RequestHeaderFieldsTooLarge;
    else if (statusString == "451 Unavailable For Legal Reasons") return ResponseStatusCode::UnavailableForLegalReasons;

        // Server errors (5xx)
    else if (statusString == "500 Internal Server Error") return ResponseStatusCode::InternalServerError;
    else if (statusString == "501 Not Implemented") return ResponseStatusCode::NotImplemented;
    else if (statusString == "502 Bad Gateway") return ResponseStatusCode::BadGateway;
    else if (statusString == "503 Service Unavailable") return ResponseStatusCode::ServiceUnavailable;
    else if (statusString == "504 Gateway Timeout") return ResponseStatusCode::GatewayTimeout;
    else if (statusString == "505 HTTP Version Not Supported") return ResponseStatusCode::HTTPVersionNotSupported;
    else if (statusString == "506 Variant Also Negotiates") return ResponseStatusCode::VariantAlsoNegotiates;
    else if (statusString == "507 Insufficient Storage") return ResponseStatusCode::InsufficientStorage;
    else if (statusString == "508 Loop Detected") return ResponseStatusCode::LoopDetected;
    else if (statusString == "510 Not Extended") return ResponseStatusCode::NotExtended;
    else if (statusString == "511 Network Authentication Required") return ResponseStatusCode::NetworkAuthenticationRequired;

    // If the input string doesn't match any known status code
    return ResponseStatusCode::Unknown;
}

enum class HttpProtocolVersion {
    HTTP1_0,
    HTTP1_1,
    HTTP2,

    Unknown
};

inline std::string getHttpProtocolVersionString (HttpProtocolVersion protocol_version) {
    switch (protocol_version) {
        case HttpProtocolVersion::HTTP1_0:
            return "HTTP/1.0";
        case HttpProtocolVersion::HTTP1_1:
            return "HTTP/1.1";
        case HttpProtocolVersion::HTTP2:
            return "HTTP/2";
        case HttpProtocolVersion::Unknown:
        default:
            return "Unknown";
    }
}

inline HttpProtocolVersion getHttpProtocolVersionEnum (std::string protocol_version_string) {
    if(protocol_version_string == "HTTP/1.0") return HttpProtocolVersion::HTTP1_0;
    else if (protocol_version_string == "HTTP/1.1") return HttpProtocolVersion::HTTP1_1;
    else if (protocol_version_string == "HTTP/2") return HttpProtocolVersion::HTTP2;

    return HttpProtocolVersion::Unknown;
}

// The method of the http request
// More info is found from here: https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods
enum class RequestMethod {
    GET,
    HEAD,
    POST,
    PUT,
    DELETE1,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH,
    UNKNOWN
};

inline RequestMethod getRequestMethodEnum(const std::string &methodString) {
    if (methodString == "GET") return RequestMethod::GET;
    else if (methodString == "HEAD") return RequestMethod::HEAD;
    else if (methodString == "POST") return RequestMethod::POST;
    else if (methodString == "PUT") return RequestMethod::PUT;
    else if (methodString == "DELETE1") return RequestMethod::DELETE1;
    else if (methodString == "CONNECT") return RequestMethod::CONNECT;
    else if (methodString == "OPTIONS") return RequestMethod::OPTIONS;
    else if (methodString == "TRACE") return RequestMethod::TRACE;
    else if (methodString == "PATCH") return RequestMethod::PATCH;

    // If the input string doesn't match any known method
    return RequestMethod::UNKNOWN;
}

inline std::string getRequestMethodString(RequestMethod method) {
    switch (method) {
        case RequestMethod::GET:
            return "GET";
        case RequestMethod::HEAD:
            return "HEAD";
        case RequestMethod::POST:
            return "POST";
        case RequestMethod::PUT:
            return "PUT";
        case RequestMethod::DELETE1:
            return "DELETE";
        case RequestMethod::CONNECT:
            return "CONNECT";
        case RequestMethod::OPTIONS:
            return "OPTIONS";
        case RequestMethod::TRACE:
            return "TRACE";
        case RequestMethod::PATCH:
            return "PATCH";
        case RequestMethod::UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

static std::string CONTENT_TYPE_HEADER = "Content-Type";
static std::string CONTENT_LENGTH_HEADER = "Content-Length";
const static std::string END_OF_HEADERS = "\r\n\r\n";

enum class ContentBodyFormat {
    // Application
    application_EDI_X12,
    application_EDIFACT,
    application_javascript,
    application_octet_stream,
    application_ogg,
    application_pdf,
    application_xhtmlXml,
    application_xShockwaveFlash,
    application_json,
    application_ldJson,
    application_xml,
    application_zip,
    application_xWwwFormUrlEncoded,

    // Audio
    audio_mpeg,
    audio_xMsWma,
    audio_vndRnRealAudio,
    audio_xWav,

    // Image
    image_gif,
    image_jpeg,
    image_png,
    image_tiff,
    image_vndMicrosoftIcon,
    image_xIcon,
    image_vndDjvu,
    image_svgXml,

    // Multipart
    multipart_mixed,
    multipart_alternative,
    multipart_related,
    multipart_formData,

    // Text
    text_css,
    text_csv,
    text_html,
    text_javascript,
    text_plain,
    text_xml,

    // Video
    video_mpeg,
    video_mp4,
    video_quicktime,
    video_xMsWmv,
    video_xMsvideo,
    video_xFlv,
    video_webm,

    Unknown
};

inline ContentBodyFormat getContentBodyFormatEnum(std::string format_string) {
    // this removes the semicolon and parameters of the header if they are present
    format_string = std::regex_replace(format_string, std::regex(";.*"), "");

    if (format_string == "application/EDI-X12") return ContentBodyFormat::application_EDI_X12;
    else if (format_string == "application/EDIFACT") return ContentBodyFormat::application_EDIFACT;
    else if (format_string == "application/javascript") return ContentBodyFormat::application_javascript;
    else if (format_string == "application/octet-stream") return ContentBodyFormat::application_octet_stream;
    else if (format_string == "application/ogg") return ContentBodyFormat::application_ogg;
    else if (format_string == "application/pdf") return ContentBodyFormat::application_pdf;
    else if (format_string == "application/xhtml+xml") return ContentBodyFormat::application_xhtmlXml;
    else if (format_string == "application/x-shockwave-flash") return ContentBodyFormat::application_xShockwaveFlash;
    else if (format_string == "application/json") return ContentBodyFormat::application_json;
    else if (format_string == "application/ld+json") return ContentBodyFormat::application_ldJson;
    else if (format_string == "application/xml") return ContentBodyFormat::application_xml;
    else if (format_string == "application/zip") return ContentBodyFormat::application_zip;
    else if (format_string == "application/x-www-form-urlencoded")
        return ContentBodyFormat::application_xWwwFormUrlEncoded;

    else if (format_string == "audio/mpeg") return ContentBodyFormat::audio_mpeg;
    else if (format_string == "audio/x-ms-wma") return ContentBodyFormat::audio_xMsWma;
    else if (format_string == "audio/vnd.rn-realaudio") return ContentBodyFormat::audio_vndRnRealAudio;
    else if (format_string == "audio/x-wav") return ContentBodyFormat::audio_xWav;

    else if (format_string == "image/gif") return ContentBodyFormat::image_gif;
    else if (format_string == "image/jpeg") return ContentBodyFormat::image_jpeg;
    else if (format_string == "image/png") return ContentBodyFormat::image_png;
    else if (format_string == "image/tiff") return ContentBodyFormat::image_tiff;
    else if (format_string == "image/vnd.microsoft.icon") return ContentBodyFormat::image_vndMicrosoftIcon;
    else if (format_string == "image/x-icon") return ContentBodyFormat::image_xIcon;
    else if (format_string == "image/vnd.djvu") return ContentBodyFormat::image_vndDjvu;
    else if (format_string == "image/svg+xml") return ContentBodyFormat::image_svgXml;

    else if (format_string == "multipart/mixed") return ContentBodyFormat::multipart_mixed;
    else if (format_string == "multipart/alternative") return ContentBodyFormat::multipart_alternative;
    else if (format_string == "multipart/related") return ContentBodyFormat::multipart_related;
    else if (format_string == "multipart/form-data") return ContentBodyFormat::multipart_formData;

    else if (format_string == "text/css") return ContentBodyFormat::text_css;
    else if (format_string == "text/csv") return ContentBodyFormat::text_csv;
    else if (format_string == "text/html") return ContentBodyFormat::text_html;
    else if (format_string == "text/javascript") return ContentBodyFormat::text_javascript;
    else if (format_string == "text/plain") return ContentBodyFormat::text_plain;
    else if (format_string == "text/xml") return ContentBodyFormat::text_xml;

    else if (format_string == "video/mpeg") return ContentBodyFormat::video_mpeg;
    else if (format_string == "video/mp4") return ContentBodyFormat::video_mp4;
    else if (format_string == "video/quicktime") return ContentBodyFormat::video_quicktime;
    else if (format_string == "video/x-ms-wmv") return ContentBodyFormat::video_xMsWmv;
    else if (format_string == "video/x-msvideo") return ContentBodyFormat::video_xMsvideo;
    else if (format_string == "video/x-flv") return ContentBodyFormat::video_xFlv;
    else if (format_string == "video/webm") return ContentBodyFormat::video_webm;

    // If the input string doesn't match any known format
    return ContentBodyFormat::Unknown;
}

inline std::string getContentBodyFormatString(ContentBodyFormat subformat) {
    switch (subformat) {
        case ContentBodyFormat::application_EDI_X12:
            return "application/EDI-X12";
        case ContentBodyFormat::application_EDIFACT:
            return "application/EDIFACT";
        case ContentBodyFormat::application_javascript:
            return "application/javascript";
        case ContentBodyFormat::application_octet_stream:
            return "application/octet-stream";
        case ContentBodyFormat::application_ogg:
            return "application/ogg";
        case ContentBodyFormat::application_pdf:
            return "application/pdf";
        case ContentBodyFormat::application_xhtmlXml:
            return "application/xhtml+xml";
        case ContentBodyFormat::application_xShockwaveFlash:
            return "application/x-shockwave-flash";
        case ContentBodyFormat::application_json:
            return "application/json";
        case ContentBodyFormat::application_ldJson:
            return "application/ld+json";
        case ContentBodyFormat::application_xml:
            return "application/xml";
        case ContentBodyFormat::application_zip:
            return "application/zip";
        case ContentBodyFormat::application_xWwwFormUrlEncoded:
            return "application/x-www-form-urlencoded";
        case ContentBodyFormat::audio_mpeg:
            return "audio/mpeg";
        case ContentBodyFormat::audio_xMsWma:
            return "audio/x-ms-wma";
        case ContentBodyFormat::audio_vndRnRealAudio:
            return "audio/vnd.rn-realaudio";
        case ContentBodyFormat::audio_xWav:
            return "audio/x-wav";
        case ContentBodyFormat::image_gif:
            return "image/gif";
        case ContentBodyFormat::image_jpeg:
            return "image/jpeg";
        case ContentBodyFormat::image_png:
            return "image/png";
        case ContentBodyFormat::image_tiff:
            return "image/tiff";
        case ContentBodyFormat::image_vndMicrosoftIcon:
            return "image/vnd.microsoft.icon";
        case ContentBodyFormat::image_xIcon:
            return "image/x-icon";
        case ContentBodyFormat::image_vndDjvu:
            return "image/vnd.djvu";
        case ContentBodyFormat::image_svgXml:
            return "image/svg+xml";
        case ContentBodyFormat::multipart_mixed:
            return "multipart/mixed";
        case ContentBodyFormat::multipart_alternative:
            return "multipart/alternative";
        case ContentBodyFormat::multipart_related:
            return "multipart/related";
        case ContentBodyFormat::multipart_formData:
            return "multipart/form-data";
        case ContentBodyFormat::text_css:
            return "text/css";
        case ContentBodyFormat::text_csv:
            return "text/csv";
        case ContentBodyFormat::text_html:
            return "text/html";
        case ContentBodyFormat::text_javascript:
            return "text/javascript";
        case ContentBodyFormat::text_plain:
            return "text/plain";
        case ContentBodyFormat::text_xml:
            return "text/xml";
        case ContentBodyFormat::video_mpeg:
            return "video/mpeg";
        case ContentBodyFormat::video_mp4:
            return "video/mp4";
        case ContentBodyFormat::video_quicktime:
            return "video/quicktime";
        case ContentBodyFormat::video_xMsWmv:
            return "video/x-ms-wmv";
        case ContentBodyFormat::video_xMsvideo:
            return "video/x-msvideo";
        case ContentBodyFormat::video_xFlv:
            return "video/x-flv";
        case ContentBodyFormat::video_webm:
            return "video/webm";

        case ContentBodyFormat::Unknown:
        default:
            return "Unknown";
    }
}

} // types
} // http

#endif //BASIC_HTTP_SERVER_HTTP_TYPES_H
