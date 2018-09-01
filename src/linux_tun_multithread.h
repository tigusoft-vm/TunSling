#ifndef LINUX_TUN_MULTITHREAD_H
#define LINUX_TUN_MULTITHREAD_H

#include "iTun.h"
#include "linuxtun.h"
#include "thread_pool.h"

class linux_tun_multithread : public iTun {
	public:
		linux_tun_multithread(std::unique_ptr<boost::asio::posix::stream_descriptor> && stream, size_t number_of_threads);
		void set_ip(const boost::asio::ip::address & addr, uint32_t mtu, bool only_reopen) override;
		size_t read_from_tun(unsigned char * data, size_t data_size) override;
		size_t send_to_tun(const unsigned char * data, size_t data_size) override;
	private:
		linuxTun<> m_linux_tun;
		ThreadPool m_thread_pool;
		void read_thread_body();
};

#endif // LINUX_TUN_MULTITHREAD_H
