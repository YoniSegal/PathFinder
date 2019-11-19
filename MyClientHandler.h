//
// Created by oriel on 1/14/19.
//

#ifndef SERVERPROJ2_MYCLIENTHANDLER_H
#define SERVERPROJ2_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include <vector>
#include "Solver.h"
#include "FileCacheManager.h"
#include "TCP.h"
#include "Util.h"
#include "Searchable.h"
#include "Searcher.h"
#include "SearchableMatrix.h"


using std::string;
using std::vector;
using std::pair;

namespace server_side {


    class MyClientHandler : public ClientHandler {

    private:

        Solver<Searchable *, Util::result> *solver;
        CacheManager *cacheManager;

    public:
        MyClientHandler(Solver<Searchable *, Util::result> *solver, CacheManager *cacheManager);

        void handleClient(int socketID) override;

    };

}


#endif //SERVERPROJ2_MYCLIENTHANDLER_H
