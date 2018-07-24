#ifndef ICRYPTO_H
#define ICRYPTO_H


class iCrypto
{
    public:
        virtual ~iCrypto() = default;

        size_t encrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, , size_t key_size, const unsigned char * output_data, size_t output_data_max_size) = 0;
        size_t decrypt(const unsigned char * input_data, size_t input_data_size, const unsigned char * key, , size_t key_size, const unsigned char * output_data, size_t output_data_max_size) = 0;
};

#endif // ICRYPTO_H
