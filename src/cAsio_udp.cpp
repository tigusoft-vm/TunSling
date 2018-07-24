#include "cAsio_udp.h"

cAsio_udp::cAsio_udp(boost::asio::ip::udp::socket && sock)
:   m_sock(std::move(sock))
{
}

size_t cAsio_udp::send(const unsigned char * data, size_t data_size, const boost::asio::ip::address & adr) {
    boost::asio::ip::udp::endpoint receiver_endpoint(adr, m_port);
    if( adr.is_v4() ) {
        m_sock.open(boost::asio::ip::udp::v4());
    } else if( adr.is_v6() ) {
        m_sock.open(boost::asio::ip::udp::v6());
    } else {
        return 0;
    }

    return m_sock.send_to(boost::asio::buffer(data, data_size), receiver_endpoint);
}

size_t cAsio_udp::recv(unsigned char * data, size_t data_size, const boost::asio::ip::address & adr, boost::asio::ip::address & adr_out) {
    boost::asio::ip::udp::endpoint receiver_endpoint(adr, m_port);
    boost::asio::ip::udp::endpoint sender_endpoint;
    if( adr.is_v4() ) {
        m_sock.open(boost::asio::ip::udp::v4());
    } else if( adr.is_v6() ) {
        m_sock.open(boost::asio::ip::udp::v6());
    } else {
        return 0;
    }

    m_sock.bind(receiver_endpoint);
    size_t ret = m_sock.receive_from(boost::asio::buffer(data, data_size), sender_endpoint);

    return ret;
}
