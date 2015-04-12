/* 
 * File:   main.cpp
 * Author: alex
 *
 * Created on April 12, 2015, 3:52 PM
 */

#include <thread>
#include <chrono>
#include <functional>
#include <fstream>

#include "asio.hpp"

#include "pion/tcp/connection.hpp"
#include "pion/http/response_writer.hpp"
#include "pion/http/streaming_server.hpp"

using namespace std;

int main() {
    pion::http::streaming_server server(2, 8882);
    server.add_method_specific_resource("GET", "/uptime", 
            // lambda to handle GET requests
            [](pion::http::request_ptr& req, pion::tcp::connection_ptr& conn) {
                // pion specific response writer creation
                auto finfun = std::bind(&pion::tcp::connection::finish, conn);
                auto writer = pion::http::response_writer::create(conn, *req, finfun);
                // actual business logic here
                std::ifstream fi{"/proc/uptime"};
                std::string uptime{}, idletime{};
                fi >> uptime;
                fi >> idletime;
                // example-only code, some JSON lib should be used here
                writer << std::string("{\"uptime\": ").append(uptime).append(",")
                        .append("\"idletime\": ").append(idletime).append("}");
                // sending response
                writer->send();
    });
    server.start();
    // signal handling should be added here, it is omitted in this example for brevity
    std::this_thread::sleep_for(std::chrono::seconds{1000});
    server.stop(true);

    return 0;
}

