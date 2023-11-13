#pragma once

#include <stddef.h>
#include <string>

extern "C" {
    size_t test_get_jwt_size(size_t source_length);
    const char* process_string(const char* input);
}