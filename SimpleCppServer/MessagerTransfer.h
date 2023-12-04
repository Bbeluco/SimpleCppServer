#ifndef MESSAGERTRANSFER_H_INCLUDED
#define MESSAGERTRANSFER_H_INCLUDED

namespace messageTransfer {
    int getReceivedMessage(int connection) {
        std::vector<char> recvData(100);
        int result = recv(connection, recvData.data(), recvData.size() - 1, 0);
        if(result == -1) {
            std::cout << "Error on getting data";
            return -1;
        }

        std::cout << "The message was: " << recvData.data() << '\n';
        return 0;
    }

    int sendMessageToUser(int connection) {
        std::string response {"Good talking to you \n"};
        int isMessageSent = send(connection, response.c_str(), response.size(), 0);

        if(isMessageSent == -1) {
            std::cout << "Error on send message to user\n";
        }

        return isMessageSent;
    }
}

#endif // MESSAGERTRANSFER_H_INCLUDED
