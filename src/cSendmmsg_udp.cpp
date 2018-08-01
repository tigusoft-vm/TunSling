#include "cSendmmsg_udp.h"

cSendmmsg_udp::cSendmmsg_udp(int socket)
:	m_socket(socket)
{
	
}

size_t cSendmmsg_udp::send(const unsigned char * data, size_t data_size, const boost::asio::ip::address & adr) {
	
	struct sockaddr_in & my_addr = msgs_q[m_q_len].addr;
	iovec & msgvec = msgs_q[m_q_len].msg;
	msghdr & msg = msgs_q[m_q_len].hdr.msg_hdr;
	std::vector<unsigned char> & msg_data = msgs_q[m_q_len].msg_data;
	msg_data.insert( msg_data.begin(), data, data + data_size );
	
	my_addr.sin_family = AF_INET; // host byte order
	my_addr.sin_port = htons( m_port ); // short, network byte order
	my_addr.sin_addr.s_addr = *(adr.to_v4().to_bytes().data());//inet_addr( "192.168.1.105" );//INADDR_ANY; // uzupełnij moim adresem IP
	memset( &( my_addr.sin_zero ), '\0', 8 ); // wyzeruj resztę struktury
	
	msgvec.iov_base = msg_data.data();
	msgvec.iov_len = msg_data.size();
	memset(&msg, 0, sizeof(msg));
	msg.msg_name = &my_addr;
	msg.msg_namelen = sizeof(my_addr);
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;
	msg.msg_iov = &msgvec;
	msg.msg_iovlen = 1;

   
/*   mmsghdr msgs[size];
   for( int i = 0; i < size; i++ )
	   memcpy( &(msgs[i].msg_hdr), &msg, sizeof(msg) );
*/   
	m_q_len++;
	if( m_q_len == m_q_max_len ) {
		size_t bytes_sended = 0;
		sendmmsg(m_socket, msgs_q.data(), m_q_len, 0);
		for( int i = 0; i <= m_q_len; i++ )
			bytes_sended += msgs_q[i].hdr.msg_len;
		m_q_len = 0;
	}
	
	return 0;
}

size_t cSendmmsg_udp::recv(unsigned char * data, size_t data_size, const boost::asio::ip::address & adr, boost::asio::ip::address & adr_out) {
	return 0;
}
