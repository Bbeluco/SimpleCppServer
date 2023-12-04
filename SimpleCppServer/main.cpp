#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include "sockaddrConfig.h"
#include "sockCreation.h"
#include "MessagerTransfer.h"

int main()
{
    int sock{socketConfig::creation()};
    if(sock == -1) {
        return EXIT_FAILURE;
    }

    sockaddr_in sockaddr{sockaddrConfig::config()};

    if(bind(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1) {
        std::cout << "Error reserving port 9000. errno: " << errno << '\n';
        return EXIT_FAILURE;
    }

    if(listen(sock, 10) == -1) {
        std::cout << "Failed to listen on socket. errno: " << errno << '\n';
        return EXIT_FAILURE;
    }

    int addrlen = sizeof(sockaddr);
    int connection = accept(sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
    if(connection == -1) {
        std::cout << "Error on extract message from queue. errno: " << errno << '\n';
        return EXIT_FAILURE;
    }

    if(messageTransfer::getReceivedMessage(connection) == -1){
        return EXIT_FAILURE;
    }
    if(messageTransfer::sendMessageToUser(connection) == -1){
        return EXIT_FAILURE;
    }
//    std::string response {"Good talking to you \n"};
//    send(connection, response.c_str(), response.size(), 0);


    close(connection);
    close(sock);
    return 0;
}
