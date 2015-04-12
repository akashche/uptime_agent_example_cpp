
cmake_minimum_required(VERSION 3.0)
project ( uptime_agent_example CXX )
# options, use SET ( OPTNAME ON CACHE BOOL "") to override
option ( STATICLIB_PION_USE_LOG4CPLUS "Use log4cplus" OFF )
option ( STATICLIB_PION_DISABLE_LOGGING "Disable logging to std out and err" OFF )
option ( STATICLIB_PION_USE_OPENSSL "Use OpenSSL" OFF )
# pion http server lib
file ( GLOB_RECURSE pion_SRC src/pion/*.cpp )
add_library ( pion STATIC ${pion_SRC} )
target_include_directories ( pion BEFORE PRIVATE include )
target_compile_options ( pion PRIVATE -g --std=c++11 -fPIC -Wall -Werror -Wextra )
target_compile_definitions ( pion PRIVATE -DASIO_STANDALONE -DASIO_HAS_STD_CHRONO )
# uptime server
add_executable ( uptime_agent src/uptime/main.cpp )
target_link_libraries ( uptime_agent pion -pthread )
target_include_directories ( uptime_agent BEFORE PRIVATE include )
target_compile_options ( uptime_agent PRIVATE -g --std=c++11 -fPIC -Wall -Werror -Wextra )
target_compile_definitions ( uptime_agent PRIVATE -DASIO_STANDALONE -DASIO_HAS_STD_CHRONO )
