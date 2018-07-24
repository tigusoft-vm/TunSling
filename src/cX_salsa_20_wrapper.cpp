#include "cX_salsa_20_wrapper.h"

unsigned char cX_salsa_20_wrapper::s_nonce[crypto_stream_NONCEBYTES];


size_t cX_salsa_20_wrapper::encrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size) {
    if(key_size != crypto_stream_KEYBYTES)
        return 0; // TODO throw invalid_argument

    size_t data_size = (output_data_max_size < input_data_size) ? output_data_max_size : input_data_size;
    crypto_stream_xor(output_data, input_data, data_size, s_nonce, key);
    return data_size;
}

size_t cX_salsa_20_wrapper::decrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size) {
    return encrypt(input_data, input_data_size, key, key_size, output_data, output_data_max_size);
}
