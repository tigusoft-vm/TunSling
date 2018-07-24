#include "node.h"

#include <array>

node::node()
{
}

void node::run() {
	std::array<unsigned char, 9000> buffer;
	while (true) {
		size_t tun_read_size = m_tun->send_to_tun(buffer.data(), buffer.size());

	}
}

