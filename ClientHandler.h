#ifndef SERVERPROJ2_CLIENTHANDLER_H
#define SERVERPROJ2_CLIENTHANDLER_H

#include <iostream>

namespace server_side{


    class ClientHandler {

    public:

        virtual void handleClient(int socketID) = 0;

        virtual ~ClientHandler() {

        }
    };

}

#endif //SERVERPROJ2_CLIENTHANDLER_H
