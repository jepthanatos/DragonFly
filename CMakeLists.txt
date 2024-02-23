cmake_minimum_required(VERSION 3.14)
project(Dragonfly)

find_package(SFML REQUIRED)
find_package(spdlog REQUIRED)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#link_libraries(stdc++fs)

add_subdirectory(src)
add_subdirectory(tests)