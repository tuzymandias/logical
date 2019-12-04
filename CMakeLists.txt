cmake_minimum_required(VERSION 3.0.0)
project(logical VERSION 0.1.0)

SET(CMAKE_CXX_FLAGS "-std=c++17")

include(CTest)
enable_testing()

include_directories(./)
add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)