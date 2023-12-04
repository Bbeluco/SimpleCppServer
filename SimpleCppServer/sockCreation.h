#include <cassert>

#ifndef SOCKCREATION_H_INCLUDED
#define SOCKCREATION_H_INCLUDED

namespace socketConfig {
    static int sockOption(int sock) {
        const int enable = 1;
        int setOption = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1;
        if(setOption) {
            std::cout << "setsockopt(SO_REUSEADDR) failed\n";
            return -1;
        }

        return setOption;
    }

    int creation() {
        int sock = socket(AF_INET, SOCK_STREAM, 0);

        if(sock == -1) {
            std::cout << "Error on create socket. errono: " << errno << '\n';
            return sock;
        }

        if(sockOption(sock) == -1){
            return -1;
        };

        return sock;
    }
}

#endif // SOCKCREATION_H_INCLUDED
