#ifndef IUDP_H
#define IUDP_H

#include <boost/asio/ip/address.hpp>

class iUdp
{
    public:
        /** Default destructor */
        virtual ~iUdp() = default;

        virtual size_t send(const unsigned char * data, size_t data_size, const boost::asio::ip::address & adr) = 0;
        virtual size_t recv(unsigned char * data, size_t data_size, const boost::asio::ip::address & adr, boost::asio::ip::address & adr_out) = 0;
};

#endif // IUDP_H
