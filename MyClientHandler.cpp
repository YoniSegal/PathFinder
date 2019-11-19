//
// Created by oriel on 1/14/19.
//

#include "MyClientHandler.h"

server_side::MyClientHandler::MyClientHandler(server_side::Solver<Searchable *, Util::result> *solver,
                                              CacheManager *cacheManager) : solver(solver),
                                                                            cacheManager(cacheManager) {}


void server_side::MyClientHandler::handleClient(int socketID) {

    string curLine;

    //currently useless. holds the problem string as is
    string wholeProblem;

    //whole info including src and dst
    vector<vector<int>> matrixInfo;
    //std::vector<std::vector<int>> matrix;

    while ("end" != (curLine = TCP::getLine(socketID))){

        wholeProblem += (curLine + "\n");

        auto splitLine = Util::explode(curLine, ',');
        vector<int> row;

        for (auto const &cell : splitLine){
            row.push_back(std::stoi(cell));
        }

        matrixInfo.push_back(row);

    }

    pair<int, int> start;
    pair<int, int> end;

    end.first = matrixInfo.back().front();
    end.second = matrixInfo.back().back();

    start.first = (matrixInfo.end() - 2)->front();
    start.second = (matrixInfo.end() - 2)->back();


    auto it = matrixInfo.begin();

    vector<vector<int>> matrix;

    for(; it != matrixInfo.end() - 2; it++)
        matrix.push_back(*it);

    auto matrice = SearchableMatrix(matrix, start, end);

    std::string solutionString;

    if (cacheManager->doesExist(wholeProblem)){
        solutionString = cacheManager->load(wholeProblem);
    } else {
        Util::result result = solver->solve(&matrice);
        solutionString = result.shortestPath;
        cacheManager->save(wholeProblem, solutionString);
    }

    TCP::sendToClient(socketID, solutionString);

}


