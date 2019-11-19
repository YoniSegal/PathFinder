//
// Created by yonisegal on 1/10/19.
//

#ifndef SERVERPROJ2_BFS_H
#define SERVERPROJ2_BFS_H


#include "BFS.h"
#include "Util.h"
#include "SearchableMatrix.h"
#include "Searchable.h"
#include "Searcher.h"

class BFS : public Searcher {

    
    Util::result search(Searchable *searchable) {
        Util::result result;

        result.developedVertex = 0;
        result.shortestPath = "";
        result.weight = 0;

        State *goalState = searchable->getGoalState();

        std::queue < State * > prioritQueue;
        
        searchable->getInitialState()->gotFrom = Start;

        prioritQueue.push((searchable->getInitialState()));

        State *cur_node;
        while (!prioritQueue.empty()) {
            cur_node = prioritQueue.front();
            prioritQueue.pop();

            if (cur_node == goalState) //finished
            {
                break;
            }

            //top
            if (cur_node->top != NULL && !cur_node->top->isInfinity && cur_node->top->gotFrom == NotSet) {
                cur_node->top->gotFrom = Down;
                prioritQueue.push(cur_node->top);

            }

            //bottom
            if (cur_node->bottom != NULL && !cur_node->bottom->isInfinity &&
                cur_node->bottom->gotFrom == NotSet) {
                cur_node->bottom->gotFrom = Up;
                prioritQueue.push(cur_node->bottom);
            }
            //left
            if (cur_node->left != NULL && !cur_node->left->isInfinity &&
                cur_node->left->gotFrom == NotSet) {
                cur_node->left->gotFrom = Right;
                prioritQueue.push(cur_node->left);
            }
            //right
            if (cur_node->right != NULL && !cur_node->right->isInfinity &&
                cur_node->right->gotFrom == NotSet) {
                cur_node->right->gotFrom = Left;
                prioritQueue.push(cur_node->right);
            }

            result.developedVertex++;

        }

        //no path exists!
        if (cur_node != goalState) {
            result.shortestPath = "";
            result.weight = -1;
            return result;
        }

        bool arrivedStart = false;

        std::string curDir;
        while (!arrivedStart) {

            result.weight += cur_node->weigth;
            switch (cur_node->gotFrom) {
                case Up:
                    cur_node = cur_node->top;
                    curDir = "Down, ";
                    break;
                case Down:
                    cur_node = cur_node->bottom;
                    curDir = "Up, ";
                    break;
                case Left:
                    cur_node = cur_node->left;
                    curDir = "Right, ";
                    break;
                case Right:
                    cur_node = cur_node->right;
                    curDir = "Left, ";
                    break;
                case Start:
                    arrivedStart = true;
                    break;
                default:
                    throw "not valid scenario";
            }
            if (!arrivedStart)
                result.shortestPath.insert(0, curDir);
        }
        result.shortestPath =
                result.shortestPath.substr(0, result.shortestPath.length() - 2);


        return result;
    }
};

#endif //SERVERPROJ2_BFS_H


