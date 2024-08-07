cmake_minimum_required(VERSION 3.5)
project(MessageSignature CXX)

file(GLOB MessageSignatureSources *.cpp *.hpp *.cc *.h)

include_directories(${CMAKE_SOURCE_DIR}/libs/crypto-cpp/src)
add_library(signer STATIC ${MessageSignatureSources})

# link starkware static libs
set (STARKWARE_ALGEBRA ${CMAKE_SOURCE_DIR}/libs/crypto-cpp/build/src/starkware/algebra/libalgebra.a)
set (STARKWARE_CRYPTO ${CMAKE_SOURCE_DIR}/libs/crypto-cpp/build/src/starkware/crypto/libcrypto.a)
set (STATIC_LIBS starkware_cpp_wrapper starkware_rust_api keccak ${STARKWARE_STARKEX} ${STARKWARE_CRYPTO} ${STARKWARE_ALGEBRA})

target_include_directories(signer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(signer ${STATIC_LIBS})