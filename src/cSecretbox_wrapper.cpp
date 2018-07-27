#include "cSecretbox_wrapper.h"
#include <stdexcept>

unsigned char cSecretbox_wrapper::s_nonce[crypto_secretbox_NONCEBYTES];


size_t cSecretbox_wrapper::encrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size) {
	if(key_size != crypto_secretbox_KEYBYTES)
		throw std::invalid_argument("Wrong key size!!!");
	if(output_data_max_size < crypto_secretbox_MACBYTES)
		throw std::invalid_argument("Wrong output data size!!!");

	size_t data_size = (output_data_max_size < (input_data_size + crypto_secretbox_MACBYTES)) ? (output_data_max_size - crypto_secretbox_MACBYTES) : input_data_size;
	crypto_secretbox_easy(output_data, input_data, data_size, s_nonce, key);
	return data_size + crypto_secretbox_MACBYTES;
}

size_t cSecretbox_wrapper::decrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size) {
	if(key_size != crypto_secretbox_KEYBYTES)
		throw std::invalid_argument("Wrong key size!!!");
	if(input_data_size < crypto_secretbox_MACBYTES)
		throw std::invalid_argument("Wrong input data size!!!");

	size_t data_size = (output_data_max_size < (input_data_size - crypto_secretbox_MACBYTES)) ? (output_data_max_size + crypto_secretbox_MACBYTES) : input_data_size;
	if(crypto_secretbox_open_easy(output_data, input_data, data_size, s_nonce, key) != 0)
		throw std::runtime_error("Message forged!!!");
	return data_size - crypto_secretbox_MACBYTES;
}
