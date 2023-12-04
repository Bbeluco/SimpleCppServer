#ifndef SOCKADDRCONFIG_H_INCLUDED
#define SOCKADDRCONFIG_H_INCLUDED

namespace sockaddrConfig {
    sockaddr_in config() {
        sockaddr_in sockaddr;
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(9000);
        sockaddr.sin_addr.s_addr = INADDR_ANY;

        return sockaddr;
    }
}

#endif // SOCKADDRCONFIG_H_INCLUDED
