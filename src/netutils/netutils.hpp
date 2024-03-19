#pragma once
#include <sys/types.h>
#include <ifaddrs.h>


namespace netutils{


struct SIOCSIFFLAGS_t
{
    bool IFF_UP;          // Interface is running.
    bool IFF_BROADCAST;   // Valid broadcast address set.
    bool IFF_DEBUG;       // Internal debugging flag.
    bool IFF_LOOPBACK;    // Interface is a loopback interface.
    bool IFF_POINTOPOINT; // Interface is a point-to-point link.
    bool IFF_RUNNING;     // Resources allocated.
    bool IFF_NOARP;       // No arp protocol, L2 destination address not set.
    bool IFF_PROMISC;     // Interface is in promiscuous mode.
    bool IFF_NOTRAILERS;  // Avoid use of trailers.
    bool IFF_ALLMULTI;    // Receive all multicast packets.
    bool IFF_MASTER;      // Master of a load balancing bundle.
    bool IFF_SLAVE;       // Slave of a load balancing bundle.
    bool IFF_MULTICAST;   // Supports multicast
    bool IFF_PORTSEL;     // Is able to select media type via ifmap.
    bool IFF_AUTOMEDIA;   // Auto media selection active.
    bool IFF_DYNAMIC;     // The addresses are lost when the interface goes down.
    bool IFF_LOWER_UP;    // Driver signals L1 up (since Linux 2.6.17)
    bool IFF_DORMANT;     // Driver signals dormant (since Linux 2.6.17)
    bool IFF_ECHO;        // Echo sent packets (since Linux 2.6.25)
};

SIOCSIFFLAGS_t getInterfaceFlags(struct ifaddrs *ifa);

}


