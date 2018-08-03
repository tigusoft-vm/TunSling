#include "clinyxtunweld.h"

cLinuxTunWeld::cLinuxTunWeld(std::unique_ptr<boost::asio::posix::stream_descriptor> && stream)
    :
      m_linux_tun(std::move(stream))
{
}

void cLinuxTunWeld::set_ip(const boost::asio::ip::address &addr, uint32_t mtu) {
    m_linux_tun.set_ip(addr, mtu);
    m_weld.resize(mtu * 10); // we can contain up to 10 packets
    m_current_data_read_ready_ptr = &(m_weld[0]);
}

size_t cLinuxTunWeld::read_from_tun(unsigned char *data, size_t data_size) {
    m_linux_tun.read_from_tun(data, data_size);
}

size_t cLinuxTunWeld::send_to_tun(const unsigned char *data, size_t data_size) {
    m_linux_tun.send_to_tun(data, data_size);
}
