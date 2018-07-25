#include "node.h"

#include <array>
#include "cX_salsa_20_wrapper.h"
#include "linuxtun.h"
#include "cAsio_udp.h"

void node::run() {
    std::array<unsigned char, 9000> buffer;
    std::array<unsigned char, crypto_stream_KEYBYTES> crypto_key;
    crypto_key.fill(0b10101010);
    boost::asio::ip::address dst_addr = boost::asio::ip::address::from_string("192.168.1.106");
    assert(m_tun != nullptr);
    assert(m_io_service != nullptr);
    m_tun->set_ip(boost::asio::ip::address::from_string("fd44:1111:2222:3333:4444:5555:6666:7777"), 1500);
	while (true) {
        size_t tun_read_size = m_tun->read_from_tun(buffer.data(), buffer.size());
        size_t encypted_message_size =
                m_crypto->encrypt(
                          buffer.data(), tun_read_size,
                          crypto_key.data(), crypto_key.size(),
                          buffer.data(), buffer.size());
        m_udp->send(buffer.data(), encypted_message_size, dst_addr);
    }
}

node node::node_factory() {
    node node_product;
    node_product.m_io_service = std::make_unique<boost::asio::io_service>();
    node_product.m_crypto = std::make_unique<cX_salsa_20_wrapper>();
    assert(node_product.m_io_service != nullptr);
    auto stream_descriptor = std::make_unique<boost::asio::posix::stream_descriptor>(*(node_product.m_io_service));
    node_product.m_tun = std::make_unique<linuxTun<>>(std::move(stream_descriptor));
    assert(stream_descriptor == nullptr);
    boost::asio::ip::udp::socket socket(*(node_product.m_io_service));
    node_product.m_udp = std::make_unique<cAsio_udp>(std::move(socket));
    return node_product;
}

