#ifndef CCRYPTOEMPTY_H
#define CCRYPTOEMPTY_H

#include "iCrypto.h"

class cCryptoEmpty : public iCrypto {
    public:
        size_t encrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size) override;
        size_t decrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, size_t key_size, unsigned char * output_data, size_t output_data_max_size) override;
};

#endif // CCRYPTOEMPTY_H
