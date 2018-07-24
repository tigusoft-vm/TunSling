#ifndef NODE_H
#define NODE_H

#include "iCrypto.h"
#include "iTun.h"
#include "iUdp.h"
#include <boost/asio/io_service.hpp>
#include <memory>

class node final {
	public:
        void run();
        static node node_factory();
        node(node &&) = default;
	private:
        node() = default;
        std::unique_ptr<boost::asio::io_service> m_io_service;
		std::unique_ptr<iCrypto> m_crypto;
		std::unique_ptr<iTun> m_tun;
		std::unique_ptr<iUdp> m_udp;

};

#endif // NODE_H
