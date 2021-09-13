
cmake_minimum_required(VERSION 3.16)

project(gfx_extensions)

find_package(fmt REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17 )

target_link_libraries(${PROJECT_NAME} fmt::fmt EGL GLESv2 )

