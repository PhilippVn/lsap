#include "lsap.hpp"
#include "netutils/netutils.hpp"

#include <iomanip>
#include <iostream>
#include <memory>
#include <cstdint>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <linux/if_link.h>
#include <cerrno>
#include <cstring>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sstream>

std::string padString(const std::string& input, size_t totalWidth, char paddingChar) {
    std::string paddedString = input;
    if (paddedString.length() < totalWidth) {
        paddedString.append(totalWidth - paddedString.length(), paddingChar);
    }
    return paddedString;
}

// TODO
// Identify all avaiable access points
// Get their ssids, security, signal strength, download and upload rate
// sort by security and signalstrength

// capabilities(7)
// CAP_NET_RAW capability needed
// sudo setcap cap_net_raw+eip /path/to/your/executable
// getcap /path/to/your/executable should display cap_net_raw+eip
int main(int argc, char *argv[])
{

    // get interface addresses
    // getifaddrs(3)
    // netdevice(7)

    struct ifaddrs *ifaddr;
    if (getifaddrs(&ifaddr) == -1)
    {
        std::cerr << "Network interface query failed: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Device Network Interfaces:" << std::endl;
    std::cout << "\n\n";
    std::cout << std::flush;
    // walk through linked list
    std::size_t i = 0;
    for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        struct sockaddr *iadrr = ifa->ifa_addr;
        if (iadrr == NULL)
            continue;

        sa_family_t family = iadrr->sa_family;
        char *name = ifa->ifa_name;

        netutils::SIOCSIFFLAGS_t intfFlags = netutils::getInterfaceFlags(ifa);

        // Display Interfaces
        std::cout << i++ << " : " << padString(name,15,' ') << ((family == AF_PACKET) ? "AF_PACKET" : (family == AF_INET) ? "AF_INET"
                                                                                          : (family == AF_INET6)  ? "AF_INET6"
                                                                                                                  : "UNKOWN");
        std::stringstream ss;
        ss << "<";
        ss << (intfFlags.IFF_UP ? "UP," : "");
        ss << (intfFlags.IFF_BROADCAST? "BROADCAST," : "");
        ss << (intfFlags.IFF_LOOPBACK ? "LOOPBACK," : "");
        ss << (intfFlags.IFF_NOARP ? "NOARP," : "");
        ss << (intfFlags.IFF_POINTOPOINT ? "POINTOPOINT," : "");
        ss << (intfFlags.IFF_MULTICAST ? "MULTICAST," : "");
        ss << (intfFlags.IFF_ALLMULTI ? "ALLMULTI," : "");
        ss << (intfFlags.IFF_PORTSEL ? "PORTSEL," : "");
        ss << (intfFlags.IFF_DYNAMIC ? "DYNAMIC," : "");

        std::string str = ss.str();
        if(str.size() > 1){
            // delete last ,
            str.pop_back();
        }

        str.append(">");

        std::cout << str << std::endl;

        if (family == AF_INET || family == AF_INET6)
        {
            char host[NI_MAXHOST];
            int s = getnameinfo(ifa->ifa_addr,
                            (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                            host, NI_MAXHOST,
                            NULL, 0, NI_NUMERICHOST);
            if (s != 0)
            {
                std::cerr << "Error getting interface adress: " << gai_strerror(s) << std::endl;
                exit(EXIT_FAILURE);
            }
            std::cout << padString("",19,' ') << "adress: "  << host << std::endl;
        }

        std::cout << "\n\n";
        std::cout << std::flush;
    }

    freeifaddrs(ifaddr);

    // socket(2)
    // socket(3)
    // packet(7)
    // create raw socket to sniff all network packets
    int socketfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (socketfd == -1)
    {
        std::cerr << "Socket creation failed:" << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    close(socketfd);

    exit(EXIT_SUCCESS);

    // TODO get a machine with Wifi
    // bind to wifi interface
}
