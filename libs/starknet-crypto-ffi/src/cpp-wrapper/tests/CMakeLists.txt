cmake_minimum_required (VERSION 3.5)

project(CppWrapperTest LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.13.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/libs/crypto-cpp/src)

add_executable(cppWrapperTest test.cpp)
target_link_libraries(cppWrapperTest starkware_cpp_wrapper starkware_rust_api    pthread)
add_test(cppWrapperTest cppWrapperTest)