#ifndef TUN_H
#define TUN_H

#include <boost/asio/ip/address.hpp>
#include <functional>


class iTun {
    public:
        virtual ~iTun() = default;

        virtual void set_ip(const boost::asio::ip::address & adr, uint32_t mtu) = 0;
        virtual size_t read_from_tun(unsigned char * data, size_t data_size) = 0;
        virtual size_t send_to_tun(const unsigned char * data, size_t data_size) = 0;
};

class iTunAsync {
	public:
		virtual ~iTunAsync() = default;
		virtual void async_read_from_tun(unsigned char * data, size_t data_size, std::function<void(size_t)> handler) = 0;
		virtual void async_write_to_tun(const unsigned char * data, size_t data_size, std::function<void(size_t)> handler) = 0;
		virtual void run() = 0; ///< equivalent to io_service.run()
};

#endif // TUN_H
