#ifndef SERVERPROJ2_MYPARALLELSERVER_H
#define SERVERPROJ2_MYPARALLELSERVER_H


#include <thread>
#include <vector>
#include "Server.h"
#include "TCP.h"


namespace server_side {

    /**
     * defines a parallel multi client server
     */
    class MyParallelServer : public Server  {

        std::shared_ptr<bool> run;
        std::thread sThread;
        std::shared_ptr<std::vector<std::thread>> clientThreads;

        void waitClients();

    public:

        MyParallelServer();

        void open(int port, ClientHandler *clientHandler) override;

        void stop() override;

        ~MyParallelServer() override{
            //delete this->keepRunning;
            //delete(clientThreads);
        }

    };



}

#endif //SERVERPROJ2_MYPARALLELSERVER_H
