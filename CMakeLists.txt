cmake_minimum_required(VERSION 3.16)
project(basic_http_server)

set(CMAKE_CXX_STANDARD 14)

add_library(http_server
        inc/http_server/TCPServer.h
        src/TCPServer.cpp

        inc/http_server/HttpRequest.h
        src/HttpRequest.cpp

        inc/http_server/HttpResponse.h
        src/HttpResponse.cpp

        inc/http_server/TCPSocket.h
        src/TCPSocket.cpp

        inc/http_server/http_types.h
        inc/http_server/HttpServerException.h)

target_include_directories(http_server PUBLIC inc)
# Add the Winsock library for Windows
if(WIN32)
    target_link_libraries(http_server PRIVATE wsock32 ws2_32)
endif()




add_executable(basic_http_server-test
        main.cpp)


target_link_libraries(basic_http_server-test http_server)