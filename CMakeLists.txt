cmake_minimum_required(VERSION 3.5)

project(Refrigerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Refrigerator main.cpp)

set(COOLPROP_STATIC_LIBRARY true)
add_subdirectory ("${CMAKE_SOURCE_DIR}/CoolProp" CoolProp)
target_link_libraries (Refrigerator CoolProp)
