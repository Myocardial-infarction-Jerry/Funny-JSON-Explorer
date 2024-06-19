cmake_minimum_required(VERSION 3.10)
project(FunnyJSONExplorer)

set(CMAKE_CXX_STANDARD 17)

# Set the CMake module path to include custom CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FetchContent)

# Fetch and make available nlohmann_json
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(json)

# Fetch and make available argparse
FetchContent_Declare(argparse GIT_REPOSITORY https://github.com/p-ranav/argparse.git)
FetchContent_MakeAvailable(argparse)

# Fetch utf8proc library
FetchContent_Declare(
  utf8proc
  GIT_REPOSITORY https://github.com/JuliaStrings/utf8proc.git
  GIT_TAG v2.6.1
)
FetchContent_MakeAvailable(utf8proc)

# Include directories
include_directories(include)

# Define source
file(GLOB SOURCE_FILES "src/*.cpp")

# Define the executable and link libraries
add_executable(fje ${SOURCE_FILES})
target_link_libraries(fje PRIVATE nlohmann_json::nlohmann_json argparse utf8proc)
