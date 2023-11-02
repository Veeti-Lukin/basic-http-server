#ifndef INCLUDED_HTTP_TCPSERVER_LINUX
#define INCLUDED_HTTP_TCPSERVER_LINUX

#include <exception>
#include <string>
#include <iostream>
#include <arpa/inet.h>
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




class TcpServer
{
public:
    TcpServer(std::string ip_address, int port);
    ~TcpServer();

    //
    void startListen();

private:
    std::string ip_address_;
    int port_;

    int socket_;
    int new_socket_;

    long incoming_message_;
    std::string server_message_;

    // defined in arpa/inet.h
    // TODO: make my own version of this
    struct sockaddr_in socket_address_;
    unsigned int socket_address_len_;

    // maximum number of connections threads the socket accepts to queue
    // if full the client connecting will be denied
    unsigned int max_connection_threads_ = 1;

    int startServer();
    void closeServer();
    void acceptConnection(int &new_socket);
    void sendResponse();
    std::string buildResponse();
};

} // namespace http
    
#endif
