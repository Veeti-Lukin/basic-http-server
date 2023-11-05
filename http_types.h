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

    UnknownStatusCode = 999
};

inline std::string getResponseStatusCodeString(ResponseStatusCode c) {
    switch (c) {
        // Informational responses (1xx)
        case ResponseStatusCode::Continue:
            return "Continue";
        case ResponseStatusCode::SwitchingProtocols:
            return "Switching Protocols";
        case ResponseStatusCode::Processing:
            return "Processing";
        case ResponseStatusCode::EarlyHints:
            return "Early Hints";

            // Successful responses (2xx)
        case ResponseStatusCode::OK:
            return "OK";
        case ResponseStatusCode::Created:
            return "Created";
        case ResponseStatusCode::Accepted:
            return "Accepted";
        case ResponseStatusCode::NonAuthoritativeInformation:
            return "Non-Authoritative Information";
        case ResponseStatusCode::NoContent:
            return "No Content";
        case ResponseStatusCode::ResetContent:
            return "Reset Content";
        case ResponseStatusCode::PartialContent:
            return "Partial Content";
        case ResponseStatusCode::MultiStatus:
            return "Multi-Status";
        case ResponseStatusCode::AlreadyReported:
            return "Already Reported";
        case ResponseStatusCode::IMUsed:
            return "IM Used";

            // Redirection messages (3xx)
        case ResponseStatusCode::MultipleChoices:
            return "Multiple Choices";
        case ResponseStatusCode::MovedPermanently:
            return "Moved Permanently";
        case ResponseStatusCode::Found:
            return "Found";
        case ResponseStatusCode::SeeOther:
            return "See Other";
        case ResponseStatusCode::NotModified:
            return "Not Modified";
        case ResponseStatusCode::UseProxy:
            return "Use Proxy";
        case ResponseStatusCode::SwitchProxy:
            return "Switch Proxy";
        case ResponseStatusCode::TemporaryRedirect:
            return "Temporary Redirect";
        case ResponseStatusCode::PermanentRedirect:
            return "Permanent Redirect";

            // Client errors (4xx)
        case ResponseStatusCode::BadRequest:
            return "Bad Request";
        case ResponseStatusCode::Unauthorized:
            return "Unauthorized";
        case ResponseStatusCode::PaymentRequired:
            return "Payment Required";
        case ResponseStatusCode::Forbidden:
            return "Forbidden";
        case ResponseStatusCode::NotFound:
            return "Not Found";
        case ResponseStatusCode::MethodNotAllowed:
            return "Method Not Allowed";
        case ResponseStatusCode::NotAcceptable:
            return "Not Acceptable";
        case ResponseStatusCode::ProxyAuthenticationRequired:
            return "Proxy Authentication Required";
        case ResponseStatusCode::RequestTimeout:
            return "Request Timeout";
        case ResponseStatusCode::Conflict:
            return "Conflict";
        case ResponseStatusCode::Gone:
            return "Gone";
        case ResponseStatusCode::LengthRequired:
            return "Length Required";
        case ResponseStatusCode::PreconditionFailed:
            return "Precondition Failed";
        case ResponseStatusCode::PayloadTooLarge:
            return "Payload Too Large";
        case ResponseStatusCode::URITooLong:
            return "URI Too Long";
        case ResponseStatusCode::UnsupportedMediaType:
            return "Unsupported Media Type";
        case ResponseStatusCode::RangeNotSatisfiable:
            return "Range Not Satisfiable";
        case ResponseStatusCode::ExpectationFailed:
            return "Expectation Failed";
        case ResponseStatusCode::IAmATeapot:
            return "I'm a teapot";
        case ResponseStatusCode::MisdirectedRequest:
            return "Misdirected Request";
        case ResponseStatusCode::UnprocessableEntity:
            return "Unprocessable Entity";
        case ResponseStatusCode::Locked:
            return "Locked";
        case ResponseStatusCode::FailedDependency:
            return "Failed Dependency";
        case ResponseStatusCode::TooEarly:
            return "Too Early";
        case ResponseStatusCode::UpgradeRequired:
            return "Upgrade Required";
        case ResponseStatusCode::PreconditionRequired:
            return "Precondition Required";
        case ResponseStatusCode::TooManyRequests:
            return "Too Many Requests";
        case ResponseStatusCode::RequestHeaderFieldsTooLarge:
            return "Request Header Fields Too Large";
        case ResponseStatusCode::UnavailableForLegalReasons:
            return "Unavailable For Legal Reasons";

            // Server errors (5xx)
        case ResponseStatusCode::InternalServerError:
            return "Internal Server Error";
        case ResponseStatusCode::NotImplemented:
            return "Not Implemented";
        case ResponseStatusCode::BadGateway:
            return "Bad Gateway";
        case ResponseStatusCode::ServiceUnavailable:
            return "Service Unavailable";
        case ResponseStatusCode::GatewayTimeout:
            return "Gateway Timeout";
        case ResponseStatusCode::HTTPVersionNotSupported:
            return "HTTP Version Not Supported";
        case ResponseStatusCode::VariantAlsoNegotiates:
            return "Variant Also Negotiates";
        case ResponseStatusCode::InsufficientStorage:
            return "Insufficient Storage";
        case ResponseStatusCode::LoopDetected:
            return "Loop Detected";
        case ResponseStatusCode::NotExtended:
            return "Not Extended";
        case ResponseStatusCode::NetworkAuthenticationRequired:
            return "Network Authentication Required";

        default:
            return "Unknown Status Code";
    }
}

inline ResponseStatusCode getResponseStatusCodeEnum(const std::string &statusString) {
    if (statusString == "Continue") return ResponseStatusCode::Continue;
    else if (statusString == "Switching Protocols") return ResponseStatusCode::SwitchingProtocols;
    else if (statusString == "Processing") return ResponseStatusCode::Processing;
    else if (statusString == "Early Hints") return ResponseStatusCode::EarlyHints;

        // Successful responses (2xx)
    else if (statusString == "OK") return ResponseStatusCode::OK;
    else if (statusString == "Created") return ResponseStatusCode::Created;
    else if (statusString == "Accepted") return ResponseStatusCode::Accepted;
    else if (statusString == "Non-Authoritative Information") return ResponseStatusCode::NonAuthoritativeInformation;
    else if (statusString == "No Content") return ResponseStatusCode::NoContent;
    else if (statusString == "Reset Content") return ResponseStatusCode::ResetContent;
    else if (statusString == "Partial Content") return ResponseStatusCode::PartialContent;
    else if (statusString == "Multi-Status") return ResponseStatusCode::MultiStatus;
    else if (statusString == "Already Reported") return ResponseStatusCode::AlreadyReported;
    else if (statusString == "IM Used") return ResponseStatusCode::IMUsed;

        // Redirection messages (3xx)
    else if (statusString == "Multiple Choices") return ResponseStatusCode::MultipleChoices;
    else if (statusString == "Moved Permanently") return ResponseStatusCode::MovedPermanently;
    else if (statusString == "Found") return ResponseStatusCode::Found;
    else if (statusString == "See Other") return ResponseStatusCode::SeeOther;
    else if (statusString == "Not Modified") return ResponseStatusCode::NotModified;
    else if (statusString == "Use Proxy") return ResponseStatusCode::UseProxy;
    else if (statusString == "Switch Proxy") return ResponseStatusCode::SwitchProxy;
    else if (statusString == "Temporary Redirect") return ResponseStatusCode::TemporaryRedirect;
    else if (statusString == "Permanent Redirect") return ResponseStatusCode::PermanentRedirect;

        // Client errors (4xx)
    else if (statusString == "Bad Request") return ResponseStatusCode::BadRequest;
    else if (statusString == "Unauthorized") return ResponseStatusCode::Unauthorized;
    else if (statusString == "Payment Required") return ResponseStatusCode::PaymentRequired;
    else if (statusString == "Forbidden") return ResponseStatusCode::Forbidden;
    else if (statusString == "Not Found") return ResponseStatusCode::NotFound;
    else if (statusString == "Method Not Allowed") return ResponseStatusCode::MethodNotAllowed;
    else if (statusString == "Not Acceptable") return ResponseStatusCode::NotAcceptable;
    else if (statusString == "Proxy Authentication Required") return ResponseStatusCode::ProxyAuthenticationRequired;
    else if (statusString == "Request Timeout") return ResponseStatusCode::RequestTimeout;
    else if (statusString == "Conflict") return ResponseStatusCode::Conflict;
    else if (statusString == "Gone") return ResponseStatusCode::Gone;
    else if (statusString == "Length Required") return ResponseStatusCode::LengthRequired;
    else if (statusString == "Precondition Failed") return ResponseStatusCode::PreconditionFailed;
    else if (statusString == "Payload Too Large") return ResponseStatusCode::PayloadTooLarge;
    else if (statusString == "URI Too Long") return ResponseStatusCode::URITooLong;
    else if (statusString == "Unsupported Media Type") return ResponseStatusCode::UnsupportedMediaType;
    else if (statusString == "Range Not Satisfiable") return ResponseStatusCode::RangeNotSatisfiable;
    else if (statusString == "Expectation Failed") return ResponseStatusCode::ExpectationFailed;
    else if (statusString == "I'm a teapot") return ResponseStatusCode::IAmATeapot;
    else if (statusString == "Misdirected Request") return ResponseStatusCode::MisdirectedRequest;
    else if (statusString == "Unprocessable Entity") return ResponseStatusCode::UnprocessableEntity;
    else if (statusString == "Locked") return ResponseStatusCode::Locked;
    else if (statusString == "Failed Dependency") return ResponseStatusCode::FailedDependency;
    else if (statusString == "Too Early") return ResponseStatusCode::TooEarly;
    else if (statusString == "Upgrade Required") return ResponseStatusCode::UpgradeRequired;
    else if (statusString == "Precondition Required") return ResponseStatusCode::PreconditionRequired;
    else if (statusString == "Too Many Requests") return ResponseStatusCode::TooManyRequests;
    else if (statusString == "Request Header Fields Too Large") return ResponseStatusCode::RequestHeaderFieldsTooLarge;
    else if (statusString == "Unavailable For Legal Reasons") return ResponseStatusCode::UnavailableForLegalReasons;

        // Server errors (5xx)
    else if (statusString == "Internal Server Error") return ResponseStatusCode::InternalServerError;
    else if (statusString == "Not Implemented") return ResponseStatusCode::NotImplemented;
    else if (statusString == "Bad Gateway") return ResponseStatusCode::BadGateway;
    else if (statusString == "Service Unavailable") return ResponseStatusCode::ServiceUnavailable;
    else if (statusString == "Gateway Timeout") return ResponseStatusCode::GatewayTimeout;
    else if (statusString == "HTTP Version Not Supported") return ResponseStatusCode::HTTPVersionNotSupported;
    else if (statusString == "Variant Also Negotiates") return ResponseStatusCode::VariantAlsoNegotiates;
    else if (statusString == "Insufficient Storage") return ResponseStatusCode::InsufficientStorage;
    else if (statusString == "Loop Detected") return ResponseStatusCode::LoopDetected;
    else if (statusString == "Not Extended") return ResponseStatusCode::NotExtended;
    else if (statusString == "Network Authentication Required")
        return ResponseStatusCode::NetworkAuthenticationRequired;

    // If the input string doesn't match any known status code
    return ResponseStatusCode::UnknownStatusCode;
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
    format_string = std::regex_replace(format_string, std::regex("\r"), "");

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
