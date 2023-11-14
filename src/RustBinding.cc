#include "RustBinding.h"

char* my_strdup(const char* str) {
    if (str == nullptr) {
        return nullptr;
    }

    size_t len = std::strlen(str) + 1; // include null character
    char* new_str = new char[len];
    std::strcpy(new_str, str);
    return new_str;
}

StringVector StringVector::from_cpp_vector_string(const std::vector<std::string>& cpp_vector_string)
{
    StringVector res;
    res.size = cpp_vector_string.size();
    res.data = new const char*[res.size];

    for (int i = 0; i < res.size; i++)
    {
        res.data[i] = my_strdup(cpp_vector_string[i].c_str());
    }

    return res;
}

RustSigner::RustSigner(const std::string& starknet_address, const std::string& starknet_private_address, const std::string& chain_id)
    : starknet_address_(starknet_address), starknet_private_address_(starknet_private_address), chain_id_(chain_id)
{}

StringVector RustSigner::get_header_list()
{
    return StringVector::from_cpp_vector_string({starknet_address_, starknet_private_address_, chain_id_});
}

extern "C" {
    size_t test_get_jwt_size(size_t source_length) {
        return 1200;
    }

    const char* process_string(const char* input) {
        std::string* input_str = new std::string(input);
        return input_str->c_str();
    }

    const char* get_string() {
        return "Hello, world!";
    }

    StringVector get_header_list(const char* starknet_address, const char* starknet_private_address, const char* chain_id) {
        return RustSigner(starknet_address, starknet_private_address, chain_id).get_header_list();
    }
}