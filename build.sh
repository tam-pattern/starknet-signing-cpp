# Building from zero everytime.
rm -rf build && mkdir build

# Overwrite CMakeLists.txt of crypto-cpp
rm -rf ./libs/crypto-cpp/CMakeLists.txt
cp ./overwrite_crypto_cpp/CMakeLists.txt ./libs/crypto-cpp/CMakeLists.txt

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