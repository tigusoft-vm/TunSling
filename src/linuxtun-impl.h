#ifndef LINUXTUNIMPL_H
#define LINUXTUNIMPL_H

#include "../cjdns-code/NetPlatform.h"
#include <linux/if.h>
#include <linux/if_tun.h>
#include <iostream>
#include <boost/asio/ip/address_v6.hpp>

template <class TStreamDescriptor>
linuxTun<TStreamDescriptor>::linuxTun(std::unique_ptr<TStreamDescriptor> && stream)
:
    m_tun_fd(open("/dev/net/tun", O_RDWR)),
    m_tun_stream(std::move(stream))
{
    if (m_tun_stream == nullptr) throw std::invalid_argument("stream i nullptr");
    if (m_tun_fd == -1) throw std::runtime_error("open /dev/net/tun error");
    m_tun_stream->assign(m_tun_fd);
    assert(m_tun_stream != nullptr);
}

template <class TStreamDescriptor>
void linuxTun<TStreamDescriptor>::set_ip(const boost::asio::ip::address & addr, uint32_t mtu) {
    const int prefix_len = 16;
    std::cout << "Configuring tuntap options: IP address: " << addr << "/" << prefix_len << " MTU=" << mtu << '\n';
    ifreq  ifr; // the if request
    std::memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    strncpy(ifr.ifr_name, "tuntest%d", IFNAMSIZ);
    int errcode_ioctl = ioctl(m_tun_fd, TUNSETIFF, static_cast<void *>(&ifr));
    if(errcode_ioctl == -1) throw std::runtime_error("ioctl error");
    t_syserr err;
    auto binary_address = addr.to_v6().to_bytes();
    err = NetPlatform_addAddress(ifr.ifr_name, binary_address.data(), prefix_len, Sockaddr_AF_INET6);
    if (err.my_code != 0) throw std::runtime_error("NetPlatform_addAddress error");
    err = NetPlatform_setMTU(ifr.ifr_name, mtu);
    if (err.my_code != 0) throw std::runtime_error("NetPlatform_setMTU error");
    assert(m_tun_stream != nullptr);
    m_tun_stream->release();
    m_tun_stream->assign(m_tun_fd);
    std::cout << "Configuring tuntap options - done\n";
}

#endif // LINUXTUNIMPL_H
