Proof of concept implementation of Uptime Agent HTTP Server in C++
==================================================================

This repository contains a basic implementation of standalone HTTP server application that returns server uptime in JSON over HTTP.

Build and start
---------------

    git clone https://bitbucket.org/alexkasko/uptime_agent_example_cpp.git
    cd uptime_agent_example_cpp
    mkdir build
    cd build
    cmake ..
    make 
    ./uptime_agent

The server will start on port 8882 and will return uptime JSON on url [http://127.0.0.1:8882/uptime](http://127.0.0.1:8882/uptime).

Server implementation details
-----------------------------

Server implementation uses stripped down version of [Pion HTTP server from Splunk](https://github.com/splunk/pion). This version does not require Boost libraries and uses [standalone ASIO networking library](https://think-async.com/Asio/AsioStandalone).

[Server implementation code](https://bitbucket.org/alexkasko/uptime_agent_example_cpp/src/4975f4d4067cbe27b8b1859a7b13f5f7f9beb201/src/uptime/main.cpp?at=master) uses Pion API to start server and registers HTTP handler on "/uptime" URL. Graceful shutdown (signal handling) is not included in this example. Pion can use OpenSSL for HTTPS and [log4cplus](https://github.com/log4cplus/log4cplus) library for logging, these features were omitted in this example.

