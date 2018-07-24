#ifndef NODE_H
#define NODE_H

#include "iCrypto.h"
#include "iTun.h"
#include "iUdp.h"
#include <boost/asio/io_service.hpp>
#include <memory>

class node final {
	public:
		node();
		void run();
	private:
		std::unique_ptr<iCrypto> m_crypto;
		std::unique_ptr<iTun> m_tun;
		std::unique_ptr<iUdp> m_udp;

};

#endif // NODE_H
