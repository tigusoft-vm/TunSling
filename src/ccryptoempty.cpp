#include "ccryptoempty.h"
#include <stdexcept>

size_t cCryptoEmpty::encrypt(const unsigned char *input_data, size_t input_data_size, const unsigned char *key, size_t key_size, unsigned char *output_data, size_t output_data_max_size) {
    if (input_data != output_data) throw std::invalid_argument("input_data != output_data");
    return input_data_size;
}

size_t cCryptoEmpty::decrypt(const unsigned char *input_data, size_t input_data_size, const unsigned char *key, size_t key_size, unsigned char *output_data, size_t output_data_max_size) {
    if (input_data != output_data) throw std::invalid_argument("input_data != output_data");
    return input_data_size;
}
