#ifndef TUN_H
#define TUN_H

#include <boost/asio/ip/address.hpp>


class iTun {
    public:
        virtual ~iTun() = default;

        virtual void set_ip(const boost::asio::ip::address & adr, uint32_t mtu) = 0;
        virtual size_t read_from_tun(unsigned char * data, size_t data_size) = 0;
        virtual size_t send_to_tun(const unsigned char * data, size_t data_size) = 0;
};

#endif // TUN_H
