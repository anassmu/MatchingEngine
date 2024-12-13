cmake_minimum_required(VERSION 3.10)
project(MatchingEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
message("C++ Standard: ${CMAKE_CXX_STANDARD}")

include_directories(include)

add_executable(MatchingEngine src/main.cpp src/OrderBook.cpp)