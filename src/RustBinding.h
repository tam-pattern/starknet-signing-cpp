#pragma once

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <vector>

// Struct to represent vector of strings
struct StringVector {
    const char** data;
    size_t size;

    static StringVector from_cpp_vector_string(const std::vector<std::string>& cpp_vector_string);
};

class RustSigner
{
private:
    std::string starknet_address_;
    std::string starknet_private_address_;
    std::string chain_id_;

public:
    RustSigner(const std::string& starknet_address, const std::string& starknet_private_address, const std::string& chain_id);
    StringVector get_header_list();
};

extern "C" {
    size_t test_get_jwt_size(size_t source_length);
    const char* process_string(const char* input);
    const char* get_string();
}