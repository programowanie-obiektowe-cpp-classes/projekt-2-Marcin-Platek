cmake_minimum_required(VERSION 3.14)
project(cpp-project CXX)

# Wyszukiwanie plików źródłowych w katalogu src
file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Tworzenie pliku wykonywalnego
add_executable(cpp-project ${SRC_FILES})

# Dodanie katalogu include
target_include_directories(cpp-project PUBLIC "${CMAKE_SOURCE_DIR}/include")

# Ustawienie standardu C++
set_target_properties(cpp-project PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)