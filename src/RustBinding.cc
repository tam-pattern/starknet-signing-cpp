#include "RustBinding.h"

extern "C" {
    size_t test_get_jwt_size(size_t source_length) {
        return 1200;
    }
}