//
// Created by yonisegal on 1/10/19.
//

#ifndef SERVERPROJ2_DFS_H
#define SERVERPROJ2_DFS_H

#include <stack>
#include <queue>
#include <fstream>
#include "Searcher.h"

class DFS : public Searcher {
    std::stack<State *> path;
    State *source;
    State *destination;
    bool found = false;

    Util::result result;


public:
    Util::result search(Searchable *searchable) override {
        source = searchable->getInitialState();
        destination = searchable->getGoalState();
        std::stack<State *> visited;
        DFSSearch(searchable, source, visited, new bool(true));

        result.shortestPath = getPath();
        return result;

//        if (found) {
//            writePath();
//        }
    }

    void setSource(State *source) {
        DFS::source = source;
    }

    void setDestination(State *destination) {
        DFS::destination = destination;
    }

    //TODO: deal with visited nodes.
    void DFSSearch(Searchable *&searchable, State *vertex, std::stack<State *> &visited,
                   bool *continueFlag) {
        visited.push(vertex);
        vertex->isMarked = true;

//        searchable->addVisited(vertex.getState());

        path.push(vertex);

        if (vertex == destination) {

            found = true;
            *continueFlag = false;
            return;
        }
        std::vector<State *> states = searchable->getAllPossibleStates(vertex);
        if (states.empty()) {
            path.pop();
        } else {
            for (int i = 0; i < states.size(); ++i) {
                if (*continueFlag && !states[i]->isMarked) {
                    DFSSearch(searchable, states[i], visited, continueFlag);
                }
            }
        }
    }

    std::string getPath() {
        std::string route;
        std::stack<State *> finalPath;
        long size = path.size();
        for (int i = 0; i < size; ++i) {
            finalPath.push(path.top());
            path.pop();
        }
        while (finalPath.size() > 1) {
            State *first = finalPath.top();
            finalPath.pop();
            State *second = finalPath.top();
            if (first->row_index < second->row_index) {
                route += "Down,";
            } else if (first->row_index > second->row_index) {
                route += "Up,";
            } else if (first->col_index < second->col_index) {
                route += "Right,";
            } else {
                route += "Left,";
            }
        }
        route = route.substr(0, route.size() - 1);
        return route;

//
//        std::ofstream solutionWriter("solutions.txt", std::ios::out | std::ios::app | std::ios::ate);
//        if (solutionWriter.is_open()) {
//            solutionWriter << route << std::endl;
//        }
//    }
    }
};


#endif //SERVERPROJ2_DFS_H
