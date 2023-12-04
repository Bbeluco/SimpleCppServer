#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        std::cout << "Error on create socket. errono: " << errno << '\n';
        return EXIT_FAILURE;
    }

    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(9000);
    sockaddr.sin_addr.s_addr = INADDR_ANY;

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

    char buffer[100];
    read(connection, buffer, 100);
    std::cout << "The message was: " << buffer << '\n';

    std::string response {"Good talking to you \n"};
    send(connection, response.c_str(), response.size(), 0);


    close(connection);
    close(sock);
    return 0;
}
