#include "netutils.hpp"
#include <sys/types.h>
#include <ifaddrs.h>
#include <bitset>
#include <iostream>

namespace netutils
{
    // getifadrs(3)
    // netdevice(7)
    struct SIOCSIFFLAGS_t getInterfaceFlags(struct ifaddrs *ifa)
    {
        unsigned int ifa_flags = ifa->ifa_flags;
        struct SIOCSIFFLAGS_t flags;
        flags.IFF_UP = ifa_flags & (1 << 0);
        flags.IFF_BROADCAST = ifa_flags & (1 << 1);
        flags.IFF_DEBUG = ifa_flags & (1 << 2);
        flags.IFF_LOOPBACK = ifa_flags & (1 << 3);
        flags.IFF_POINTOPOINT = ifa_flags & (1 << 4);
        flags.IFF_RUNNING = ifa_flags & (1 << 5);
        flags.IFF_NOARP = ifa_flags & (1 << 6);
        flags.IFF_PROMISC = ifa_flags & (1 << 7);
        flags.IFF_NOTRAILERS = ifa_flags & (1 << 8);
        flags.IFF_ALLMULTI = ifa_flags & (1 << 9);
        flags.IFF_MASTER = ifa_flags & (1 << 10);
        flags.IFF_SLAVE = ifa_flags & (1 << 11);
        flags.IFF_MULTICAST = ifa_flags & (1 << 12);
        flags.IFF_PORTSEL = ifa_flags & (1 << 13);
        flags.IFF_AUTOMEDIA = ifa_flags & (1 << 14);
        flags.IFF_DYNAMIC = ifa_flags & (1 << 15);
        flags.IFF_LOWER_UP = ifa_flags & (1 << 16);
        flags.IFF_DORMANT = ifa_flags & (1 << 17);
        flags.IFF_ECHO = ifa_flags & (1 << 18);
        return flags;
    }
}