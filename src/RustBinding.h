#pragma once

#include <stddef.h>
#include <cstring>
#include <string>
#include <vector>

#include "Account.hpp"
#include "Order.hpp"
#include "StarkCurveSigner.hpp"
#include "StarknetDomain.hpp"
#include <starkware/algebra/big_int.h>
#include <starkware/algebra/prime_field_element.h>

using namespace starkware;
using namespace signer;

// Struct to represent vector of strings
struct StringVector {
    const char** data;
    size_t size;

    static StringVector from_cpp_vector_string(const std::vector<std::string>& cpp_vector_string);
};

class RustSigner
{
private:
    const BigInt<4> starknet_address_;
    const BigInt<4> starknet_private_key_;
    std::string chain_id_;
    const KeyPair key_pair_;
    const PrimeFieldElement starknet_address_prime_field_element_;

public:
    RustSigner(const std::string& starknet_address, const std::string& starknet_private_address, const std::string& chain_id);
    StringVector get_headers_list();
};