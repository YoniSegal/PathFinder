#ifndef SERVERPROJ2_ICACHEMANAGER_H
#define SERVERPROJ2_ICACHEMANAGER_H

#include <string>

//namespace server_side {

    class CacheManager {

    public:

        virtual bool doesExist(std::string key) = 0;

        virtual std::string load(std::string key) = 0;

        virtual void save(std::string key, std::string solution) = 0;

    };

//}




#endif //SERVERPROJ2_ICACHEMANAGER_H
