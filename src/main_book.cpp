
#include <iostream>

#include <cstring>




int main_engine_book() {
	constexpr int max_mq = 256;
	constexpr int use_mq = 16;
	static_assert( use_mq <= max_mq );
	std::array<int, max_mq> tun_fds;
	tun_alloc_mq("tunB", max_mq, &tun_fds.data());

	return 0;
}

