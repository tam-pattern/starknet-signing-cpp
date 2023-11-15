#include "RustBinding.h"

using namespace starkware;

// Utils functions
char* my_strdup(const char* str) {
    if (str == nullptr) {
        return nullptr;
    }

    size_t len = std::strlen(str) + 1; // include null character
    char* new_str = new char[len];
    std::strcpy(new_str, str);
    return new_str;
}

BigInt<4> hex_string_to_big_int(const std::string &hex_str) {
  BigInt<4> result = BigInt<4>::Zero();

  // Start with 2nd letter to skip '0x'
  size_t hex_str_len = hex_str.size();
  size_t i = (hex_str[0] == '0' && hex_str[1] == 'x') ? 2 : 0;

  // [module] should be big enough, in this case [modulo] = 16 ^ 65 - 1
  BigInt<4> modulo =
      0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff_Z;

  // Loop through each letter in [hex_str] and at it to [result].
  while (i < hex_str_len) {
    uint64_t hexDigit = bigint::details::HexCharToUint64(hex_str[i]);
    result = BigInt<4>::MulMod(result, (BigInt<4>)16, modulo);
    result = result + (BigInt<4>)hexDigit;

    i++;
  }

  return result;
}

BigInt<4> double_to_big_int(double val) {
  uint64_t integer_val = val * 100000000;

  return Uint256(integer_val);
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
    :   starknet_address_(hex_string_to_big_int(starknet_address)),
        starknet_private_key_(hex_string_to_big_int(starknet_private_address)),
        chain_id_(chain_id),
        key_pair_(starknet_private_key_),
        starknet_address_prime_field_element_(
            PrimeFieldElement::FromBigInt(starknet_address_))
{}

StringVector RustSigner::get_headers_list()
{
    std::vector<std::string> headers_list = Account(starknet_address_prime_field_element_, chain_id_, key_pair_).getHeadersList("");
    return StringVector::from_cpp_vector_string(headers_list);
}

extern "C" {
    StringVector get_headers_list_from_cpp(const char* starknet_address, const char* starknet_private_address, const char* chain_id) {
        return RustSigner(starknet_address, starknet_private_address, chain_id).get_headers_list();
    }
}