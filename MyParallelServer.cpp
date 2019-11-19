//
// Created by uriel on 1/13/19.
//

#include "MyParallelServer.h"

server_side::MyParallelServer::MyParallelServer() {

    this->run = std::make_shared<bool>();
    *this->run = true;

    //TODO: change to yoni's smart pointer
    //this->clientThreads = new std::vector<std::thread>;
    this->clientThreads = std::make_shared<std::vector<std::thread>>();

}


void server_side::MyParallelServer::open(int port, server_side::ClientHandler *clientHandler) {
    sThread = std::thread([](int port, std::shared_ptr<std::vector<std::thread>> clientThreads,
                                  server_side::ClientHandler *clientHandler, std::shared_ptr<bool> run) {

        int mainSktId = server_side::TCP::readPort(port);

        bool first = true;

        while (*run) {

            std::cout << "waiting for client" << std::endl;
            int clientSockFd = server_side::TCP::Connect(mainSktId);

            //determine timeout only after first client
            timeval timeout;
            timeout.tv_sec = 10;
            timeout.tv_usec = 0;

            setsockopt(mainSktId, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

            if (clientSockFd <= -1) {

                if (!first) {
                    //break if timeout
                    break;
                } else {
                    continue;
                }

            } else if (first) {
                first = false;
            }

            std::cout << "accepted" << std::endl;

            //add each client thread to the threads list
            clientThreads->push_back(std::thread([clientHandler, clientSockFd]() {

                clientHandler->handleClient(clientSockFd);

                //close client socket
                server_side::TCP::closeSocket(clientSockFd);

            }));

        }

        TCP::closeSocket(mainSktId);

    }, port, this->clientThreads, clientHandler, run);

    sThread.join();

    for (int i = 0; i < clientThreads->size(); ++i) {
        (*clientThreads)[i].join();
    }

}


void server_side::MyParallelServer::stop() {

    *(this->run) = false;

    //wait for the thread to end
    sThread.join();
    //wait for all clients to end
    for (int i = 0; i < clientThreads->size(); ++i) {
        (*clientThreads)[i].join();
    }
}