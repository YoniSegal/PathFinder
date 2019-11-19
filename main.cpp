#include <string>
#include "MyParallelServer.h"
#include "FileCacheManager.h"
#include "MyClientHandler.h"

#include "SearchableMatrix.h"
#include "SolverToSearcher.h"

#include "AStar.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include "BFS.h"
#include "MySerialServer.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>


using namespace server_side;

int main(int argc, char **argv) {

    if(argc < 1) throw "usage: <executable> <port>";

    int port = std::stoi(argv[1]);

    auto solver = new SolverToSearcher(new AStar());

    auto cacheManager = new FileCacheManager();

    ClientHandler* clientHandler = new MyClientHandler(solver, cacheManager);

    auto myServer = new server_side::MyParallelServer();

    myServer->open(port, clientHandler);

    delete solver;
    delete cacheManager;
    delete clientHandler;
    delete myServer;

    return 0;
}

