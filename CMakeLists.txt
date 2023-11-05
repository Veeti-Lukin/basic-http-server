cmake_minimum_required(VERSION 3.26)
project(basic_http_server)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(basic_http_server
        TCPServer.cpp
        TCPServer.h
        http_types.h
        HttpRequest.cpp
        HttpRequest.h
        #HttpResponse.cpp
        #HttpResponse.h
        main.cpp
        TCPSocket.cpp
        TCPSocket.h
        HttpServerException.h)

# Add the Winsock library for Windows
if(WIN32)
    target_link_libraries(basic_http_server PRIVATE wsock32 ws2_32)
endif()