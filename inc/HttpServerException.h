#ifndef BASIC_HTTP_SERVER_HTTPSERVEREXCEPTION_H
#define BASIC_HTTP_SERVER_HTTPSERVEREXCEPTION_H

#include <exception>
#include <string>
#include <vector>

namespace http {

// Exception class, of which instances will be thrown in case of errors
// or faulty use of the server class
class HTTP_SERVER_EXCEPTION : public std::exception
{
public:
    // Default constructor where  error message is given as parameter
    HTTP_SERVER_EXCEPTION(const std::string msg) :
            message_("Error: "+msg){}
    // Constructor where error message can have placeholders that are marked with "*"
    // values from *values_to_format* will be formatted in order to these spots
    HTTP_SERVER_EXCEPTION(const std::string msg,
                          std::vector<std::string> values_to_format) :
            message_("Error: " + msg), values_to_format_(values_to_format)
    {
        // format the values to placeholder spots
        for (std::string& value : values_to_format)
        {
            message_.replace(message_.find('*'), 1, value);

        }
    }

    virtual const char* what() const noexcept override
    {
        return message_.c_str();
    }

private:
    std::string message_;
    std::vector<std::string> values_to_format_;
};

} // http

#endif //BASIC_HTTP_SERVER_HTTPSERVEREXCEPTION_H
