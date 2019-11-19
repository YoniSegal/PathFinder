
#ifndef SERVERPROJ2_MYSERIALSERVER_H
#define SERVERPROJ2_MYSERIALSERVER_H

#include <thread>
#include "Server.h"

namespace server_side{

    class MySerialServer : public Server  {

        std::shared_ptr<bool> run;
        std::thread serverThread;
        int mainSocketId;

    public:

        // maybe intializ bool in cunstructor
        //MySerialServer();

        void open(int port, ClientHandler *clientHandler) override;

        void stop() override;
//dss
    };

}



#endif //SERVERPROJ2_MYSERIALSERVER_H
