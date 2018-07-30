#include "node.h"

#include <array>
#include "cSecretbox_wrapper.h"
#include "linuxtun.h"
#include "cAsio_udp.h"
#include <thread>

void node::run() {
	std::array<unsigned char, crypto_secretbox_KEYBYTES> crypto_key;
    crypto_key.fill(0b10101010);
    boost::asio::ip::address dst_addr = boost::asio::ip::address::from_string("192.168.1.66");
    assert(m_tun != nullptr);
    assert(m_io_service != nullptr);
    m_tun->set_ip(boost::asio::ip::address::from_string("fd44:1111:2222:3333:4444:5555:6666:7777"), 1500);
	while (true) {
        std::vector<unsigned char> buffer(9000);
        size_t tun_read_size = m_tun->read_from_tun(buffer.data(), buffer.size());
        std::thread thr([=,buffer{move(buffer)}]() mutable {
                size_t encypted_message_size =
                m_crypto->encrypt(
                          buffer.data(), tun_read_size,
                          crypto_key.data(), crypto_key.size(),
                          buffer.data(), buffer.size());
                std::lock_guard<std::mutex> lg(m_udp_mutex);
                size_t udp_sended = m_udp->send(buffer.data(), encypted_message_size, dst_addr);
        });
        thr.detach();
//        std::cout << "readed from tun " << tun_read_size << "B\n";
        
//        std::cout << "encrypted\n";
        
//        std::cout << "sended via udp " <<  udp_sended << "\n";
    }
}

std::unique_ptr<node> node::node_factory() {
    std::unique_ptr<node> node_product = std::make_unique<node>();
    node_product->m_io_service = std::make_unique<boost::asio::io_service>();
	node_product->m_crypto = std::make_unique<cSecretbox_wrapper>();
    assert(node_product->m_io_service != nullptr);
    auto stream_descriptor = std::make_unique<boost::asio::posix::stream_descriptor>(*(node_product->m_io_service));
    node_product->m_tun = std::make_unique<linuxTun<>>(std::move(stream_descriptor));
    assert(stream_descriptor == nullptr);
    boost::asio::ip::udp::socket socket(*(node_product->m_io_service));
    socket.open(boost::asio::ip::udp::v4());
    node_product->m_udp = std::make_unique<cAsio_udp>(std::move(socket));
    return node_product;
}

