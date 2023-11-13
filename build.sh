if [ $# -eq 1 ]; then
    REPO_DIR=$1
    # Fetch latest commit of summodules
    cd ${REPO_DIR}
    git submodule update --init --recursive --remote
else
    REPO_DIR=${PWD}
fi

# Building from zero everytime.
rm -rf ${REPO_DIR}/build && mkdir ${REPO_DIR}/build

rm -rf ${REPO_DIR}/libs/crypto-cpp/build
mkdir ${REPO_DIR}/libs/crypto-cpp/build && cd ${REPO_DIR}/libs/crypto-cpp/build

# Build crypto-cpp
cmake -DCMAKE_BUILD_TYPE=Release .. && make

# Run conan to install libcurl
# conan install . --build=missing
# This is additional command to force gcc V13 >> -s compiler.version=13
cd ${REPO_DIR}/build

# Build whole project
cmake -DCMAKE_BUILD_TYPE=Release .. && make