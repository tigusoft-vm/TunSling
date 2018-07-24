#ifndef ICRYPTO_H
#define ICRYPTO_H

#include <cstddef>

class iCrypto
{
    public:
        virtual ~iCrypto() = default;

        virtual size_t encrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size) = 0;
        virtual size_t decrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size) = 0;
};

#endif // ICRYPTO_H
