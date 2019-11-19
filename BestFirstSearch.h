//
// Created by oriel on 1/15/19.
//

#ifndef SERVERPROJ2_BESTFIRSTSEARCH_H
#define SERVERPROJ2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include <queue>
#include "Util.h"

// for priority queue of std
class Compare
{
public:
    bool operator() (State *a, State *b)
    {
        return a->weigth > b->weigth;
    }
};

class BestFirstSearch : public Searcher {

public:
    Util::result search(Searchable *searchable) {

        Util::result result;

        result.developedVertex = 0;
        result.shortestPath = "";
        result.weight = 0;
        State* goalState;
        goalState = searchable->getGoalState();

        std::priority_queue<State *, std::vector<State *>, Compare> priorityQueue;

        searchable->getInitialState()->gotFrom = Start;

        priorityQueue.push((searchable->getInitialState()));

        State *cur_node;
        while (!priorityQueue.empty())
        {
            cur_node = priorityQueue.top();
            priorityQueue.pop();

            if (cur_node == goalState) //finished
            {
                break;
            }



            //top
            if (cur_node->top != NULL && !cur_node->top->isInfinity && cur_node->top->gotFrom == NotSet)
            {
                cur_node->top->gotFrom = Down;
                priorityQueue.push(cur_node->top);

            }

            //bottom
            if (cur_node->bottom != NULL && !cur_node->bottom->isInfinity && cur_node->bottom->gotFrom == NotSet)
            {
                cur_node->bottom->gotFrom = Up;
                priorityQueue.push(cur_node->bottom);
            }
            //left
            if (cur_node->left != NULL && !cur_node->left->isInfinity && cur_node->left->gotFrom == NotSet)
            {
                cur_node->left->gotFrom = Right;
                priorityQueue.push(cur_node->left);
            }
            //right
            if (cur_node->right != NULL && !cur_node->right->isInfinity && cur_node->right->gotFrom == NotSet)
            {
                cur_node->right->gotFrom = Left;
                priorityQueue.push(cur_node->right);
            }

            result.developedVertex++;

        }

        //no path exists!
        if (cur_node != goalState){
            result.shortestPath = "";
            result.weight = -1;
            return result;
        }


        bool arrivedStart = false;

        std::string curDirection;
        while (!arrivedStart)
        {

            result.weight += cur_node->weigth;
            switch (cur_node->gotFrom)
            {
                case Up:
                    cur_node = cur_node->top;
                    curDirection = "Down, ";
                    break;
                case Down:
                    cur_node = cur_node->bottom;
                    curDirection = "Up, ";
                    break;
                case Left:
                    cur_node = cur_node->left;
                    curDirection = "Right, ";
                    break;
                case Right:
                    cur_node = cur_node->right;
                    curDirection = "Left, ";
                    break;
                case Start:
                    arrivedStart = true;
                    break;
                default:
                    throw "no such direction";
            }
            if (!arrivedStart)
                result.shortestPath.insert(0, curDirection);
        }
        result.shortestPath =
                result.shortestPath.substr(0, result.shortestPath.length() - 2);

        return result;

    }

};


#endif //SERVERPROJ2_BESTFIRSTSEARCH_H
