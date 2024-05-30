cmake_minimum_required(VERSION 3.10)
project(FunnyJSONExplorer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

include(FetchContent)
FetchContent_Declare(argparse GIT_REPOSITORY https://github.com/p-ranav/argparse.git)
FetchContent_MakeAvailable(argparse)

include_directories(include)

add_executable(fje src/main.cpp src/FunnyJSONExplorer.cpp)
target_link_libraries(fje PRIVATE nlohmann_json::nlohmann_json argparse)

set_target_properties(fje PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
