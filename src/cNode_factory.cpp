#include "cNode_factory.h"
#include <array>
#include "cSecretbox_wrapper.h"
#include "linuxtun.h"
#include "cAsio_udp.h"
#include "cSendmmsg_udp.h"
#include <thread>

std::unique_ptr<node> cNode_factory::create_node( const boost::program_options::variables_map & vm ) {
	std::unique_ptr<node> ret = std::make_unique<node>();
	
	ret->m_dst_addr = boost::asio::ip::address::from_string(vm["address"].as<std::string>());
	
	//Create tun
	ret->m_io_service = std::make_unique<boost::asio::io_service>();
	assert(ret->m_io_service != nullptr);
	auto stream_descriptor = std::make_unique<boost::asio::posix::stream_descriptor>(*(ret->m_io_service));
	ret->m_tun = std::make_unique<linuxTun<>>(std::move(stream_descriptor));
	assert(stream_descriptor == nullptr);
	
	//Create crypto
	ret->m_crypto = std::make_unique<cSecretbox_wrapper>();
	
	//Create UDP
	std::string stdUdp = vm["UDP"].as<std::string>();
	if( stdUdp == "Asio" ) {
		boost::asio::ip::udp::socket socket(*(ret->m_io_service));
		socket.open(boost::asio::ip::udp::v4());
		ret->m_udp = std::make_unique<cAsio_udp>(std::move(socket));
	} else if( stdUdp == "Sendmmsg" ) {
		int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		ret->m_udp = std::make_unique<cSendmmsg_udp>(sockfd);
	} else
		throw std::runtime_error( "Unknown UDP version" );

	//Create thread pool
	int threds = vm["threds"].as<int>();
	if( threds == 0 ) {
		
	} else if( threds > 0 ) {
		ret->m_thread_pool = std::make_unique<ThreadPool>(threds);
	} else
		throw std::runtime_error( "Wrong thred number" );
	
	return ret;
}
