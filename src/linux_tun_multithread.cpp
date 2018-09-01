#include "linux_tun_multithread.h"

linux_tun_multithread::linux_tun_multithread(std::unique_ptr<boost::asio::posix::stream_descriptor> && stream, size_t number_of_threads)
:
	m_linux_tun(std::move(stream)),
	m_thread_pool(number_of_threads)
{
}

void linux_tun_multithread::set_ip(const boost::asio::ip::address &addr, uint32_t mtu) {
	m_linux_tun.set_ip(addr, mtu);
}

size_t linux_tun_multithread::read_from_tun(unsigned char *data, size_t data_size) {
	return 0;
}

size_t linux_tun_multithread::send_to_tun(const unsigned char *, size_t) {
	std::abort(); // not implemented yet
}

void linux_tun_multithread::read_thread_body() {
	/////////
}
