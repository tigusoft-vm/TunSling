#ifndef CSECRETBOX_WRAPPER_H
#define CSECRETBOX_WRAPPER_H

#include "iCrypto.h"
#include <sodium/crypto_secretbox.h>


class cSecretbox_wrapper : public iCrypto
{
	static unsigned char s_nonce[crypto_secretbox_NONCEBYTES];
	public:
		/** Default destructor */
		virtual ~cSecretbox_wrapper() = default;

		virtual size_t encrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size);
		virtual size_t decrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size);
};

#endif // CSECRETBOX_WRAPPER_H
