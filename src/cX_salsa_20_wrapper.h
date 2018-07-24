#ifndef CX_SALSA_20_WRAPPER_H
#define CX_SALSA_20_WRAPPER_H

#include "iCrypto.h"
#include <sodium/crypto_stream.h>


class cX_salsa_20_wrapper : public iCrypto
{
    static unsigned char s_nonce[crypto_stream_NONCEBYTES];
    public:
        /** Default destructor */
        virtual ~cX_salsa_20_wrapper() = default;

        virtual size_t encrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size);
        virtual size_t decrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size);
};

#endif // CX_SALSA_20_WRAPPER_H
