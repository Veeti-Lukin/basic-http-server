cmake_minimum_required(VERSION 3.26)
project(basic_http_server)

set(CMAKE_CXX_STANDARD 14)

#include_directories(
#        inc
#        src)
add_library(http_server
        src/TCPServer.cpp
        inc/TCPServer.h

        src/HttpRequest.cpp
        inc/HttpRequest.h

        src/HttpResponse.cpp
        inc/HttpResponse.h

        src/TCPSocket.cpp
        inc/TCPSocket.h

        inc/http_types.h
        inc/HttpServerException.h)

target_include_directories(http_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# Add the Winsock library for Windows
if(WIN32)
    target_link_libraries(http_server PRIVATE wsock32 ws2_32)
endif()




add_executable(basic_http_server-test
        main.cpp)


target_link_libraries(basic_http_server-test http_server)