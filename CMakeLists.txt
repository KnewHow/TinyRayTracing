cmake_minimum_required(VERSION 3.0.0)
project(TinyRayTracer VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

add_executable(TinyRayTracer main.cpp geometry.h geometry.cpp image.h image.cpp renderer.h renderer.cpp global.h sphere.h sphere.cpp material.h material.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
