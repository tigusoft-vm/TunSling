
#include <iostream>

#include <cstring>

// https://www.kernel.org/doc/Documentation/networking/tuntap.txt
  #include <linux/if.h>
  #include <linux/if_tun.h>

  int tun_alloc_mq(char *dev, int queues, int *fds)
  {
      struct ifreq ifr;
      int fd, err, i;

      if (!dev)
          return -1;

      memset(&ifr, 0, sizeof(ifr));
      /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
       *        IFF_TAP   - TAP device
       *
       *        IFF_NO_PI - Do not provide packet information
       *        IFF_MULTI_QUEUE - Create a queue of multiqueue device
       */
      ifr.ifr_flags = IFF_TAP | IFF_NO_PI | IFF_MULTI_QUEUE;
      strcpy(ifr.ifr_name, dev);

      for (i = 0; i < queues; i++) {
          if ((fd = open("/dev/net/tun", O_RDWR)) < 0)
             goto err;
          err = ioctl(fd, TUNSETIFF, (void *)&ifr);
          if (err) {
             close(fd);
             goto err;
          }
          fds[i] = fd;
      }

      return 0;
  err:
      for (--i; i >= 0; i--)
          close(fds[i]);
      return err;
  }
// from kernel docs



int main_engine_book() {
	constexpr int max_mq = 256;
	constexpr int use_mq = 16;
	static_assert( use_mq <= max_mq );
	std::array<int, max_mq> tun_fds;
	tun_alloc_mq("tunB", max_mq, &tun_fds.data());

	return 0;
}

