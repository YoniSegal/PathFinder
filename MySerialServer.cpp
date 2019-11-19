
#include "MySerialServer.h"
#include "TCP.h"

void server_side::MySerialServer::open(int port, server_side::ClientHandler *clientHandler) {

    mainSocketId = server_side::TCP::readPort(port);
    //change to yoni's smart pointer
    this->run = std::make_shared<bool>();
    *this->run = true;

    serverThread = std::thread([](int mainSocketId, ClientHandler *clientHandler, std::shared_ptr<bool> run) {
        while (*run) {

            std::cout<<"waiting for client"<<std::endl;

            int clientSockFd = server_side::TCP::Connect(mainSocketId);

            //determine timeout only after first client
            timeval timeout;
            timeout.tv_sec = 10;
            timeout.tv_usec = 0;

            setsockopt(mainSocketId, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

            // if no client was accepted
            if (clientSockFd < 0) {
                if (errno == EWOULDBLOCK) {
                    //TODO: stop
                    std::cout << "timeout!" << std::endl;
                    exit(2);
                } else {
                    perror("other error");
                    exit(3);
                }
            }

            std::cout<<"accepted"<<std::endl;

            clientHandler->handleClient(clientSockFd);

            //close client socket
            server_side::TCP::closeSocket(clientSockFd);

        }
    }, mainSocketId, clientHandler, run);

}

void server_side::MySerialServer::stop() {

    *run = false;
    //let the thread end
    serverThread.join();
    server_side::TCP::closeSocket(mainSocketId);

    //if not doing yoni's so delete the bool run

    //close files
    //join
    //close connection
    //free memory
}
