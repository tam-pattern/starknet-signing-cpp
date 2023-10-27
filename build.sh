# Building from zero everytime.
rm -rf build && mkdir build

# Overwrite CMakeLists.txt files to remove test
rm -rf ./libs/crypto-cpp/CMakeLists.txt
cp ./overwrite_crypto_cpp/CMakeLists.txt ./libs/crypto-cpp/CMakeLists.txt
# starkware
cp ./overwrite_crypto_cpp/CMakeLists_starkware.txt ./libs/crypto-cpp/src/starkware/CMakeLists.txt
# algebra
cp ./overwrite_crypto_cpp/CMakeLists_algebra.txt ./libs/crypto-cpp/src/starkware/algebra/CMakeLists.txt
# crypto
cp ./overwrite_crypto_cpp/CMakeLists_crypto.txt ./libs/crypto-cpp/src/starkware/crypto/CMakeLists.txt
# starkex
cp ./overwrite_crypto_cpp/CMakeLists_starkex.txt ./libs/crypto-cpp/src/starkware/starkex/CMakeLists.txt

cd ./libs/crypto-cpp && rm -rf build
mkdir build && cd build

# Build crypto-cpp
cmake -DCMAKE_BUILD_TYPE=Release .. && make

# Return to the root
cd ../../../
cd ./libs/curlpp

# Run conan to install libcurl
# conan install . --build=missing
# This is additional command to force gcc V13 >> -s compiler.version=13
cd ../../build

# Build whole project
cmake -DCMAKE_BUILD_TYPE=Release .. && make