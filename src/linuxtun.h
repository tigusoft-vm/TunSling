#ifndef LINUXTUN_H
#define LINUXTUN_H

#include "iTun.h"
#include <boost/asio/posix/stream_descriptor.hpp>
#include <memory>

template<class TStreamDescriptor = boost::asio::posix::stream_descriptor>
class linuxTun final : public iTun {
    public:
        linuxTun(std::unique_ptr<TStreamDescriptor> && stream);
        void set_ip(const boost::asio::ip::address & addr, uint32_t mtu) override;
        size_t read_from_tun(unsigned char * data, size_t data_size) override;
        size_t send_to_tun(const unsigned char * data, size_t data_size) override;
    private:
        const int m_tun_fd; ///< the unix file descriptor. -1 is closed (this should not happen in correct object)
        std::unique_ptr<TStreamDescriptor> m_tun_stream;
};

#include "linuxtun-impl.h"

#endif // LINUXTUN_H
