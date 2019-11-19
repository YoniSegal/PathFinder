#ifndef SERVERPROJ2_TCPSERVER_H
#define SERVERPROJ2_TCPSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

/**
 * static class for TCP server connection
 */

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

/**
 * static class for TCP server connection
 */


namespace server_side {

    /**
     * static class for TCP server communications
     */
    class TCP {

    public:
        //return new main socketId
        static int readPort(int serverPort);

        //return new socketId
        static int Connect(int mainSocketId);

        static std::string getLine(int socketId);

        static void sendToClient(int socketId, std::string message);

        static void closeSocket(int socketId);


    };

}


#endif //SERVERPROJ2_TCPSERVER_H
