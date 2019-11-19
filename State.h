//
// Created by yonisegal on 1/10/19.
//

#ifndef SERVERPROJ2_STATE_H
#define SERVERPROJ2_STATE_H
#include <string>
#include "Util.h"

class State
{

public:

    State *top;
    State *bottom;
    State *left;
    State *right;


    int weigth;
    bool isInfinity;
    bool isMarked;
    Directions gotFrom;
    unsigned int row_index;
    unsigned int col_index;

    State(int weigth) : top(NULL), bottom(NULL), left(NULL), right(NULL), weigth(weigth), isMarked(false) {}

    std::vector<State *> getNeighbors() {
        std::vector<State *> ret;

        if (bottom != NULL)
            ret.push_back(bottom);
        if (top != NULL)
            ret.push_back(top);
        if (left != NULL)
            ret.push_back(left);
        if (right != NULL)
            ret.push_back(right);
        return ret;
    }

};

#endif //SERVERPROJ2_STATE_H
