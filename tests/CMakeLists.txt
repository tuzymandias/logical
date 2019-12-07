if (UNIX)
    find_package(GTest)
    if(NOT GTest_FOUND)
        return()
    endif()
endif()

include_directories("${GTEST_INCLUDE_DIRS}")

add_executable(static_tests_bin static_tests.cpp)