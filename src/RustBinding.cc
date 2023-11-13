#include "RustBinding.h"

extern "C" {
    size_t test_get_jwt_size(size_t source_length) {
        return 1200;
    }

    const char* process_string(const char* input) {
        std::string input_str(input);

        // Return this string
        return input_str.c_str();
    }
}