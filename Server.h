#ifndef SERVERPROJ2_ISERVER_H
#define SERVERPROJ2_ISERVER_H

#include "ClientHandler.h"

namespace server_side{

    class Server{

    public:

        virtual void open(int port, ClientHandler *clientHandler) = 0;

        virtual void stop() = 0;

        virtual ~Server() {

        }
    };

}

#endif //SERVERPROJ2_ISERVER_H
