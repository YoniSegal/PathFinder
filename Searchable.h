//
// Created by yonisegal on 1/10/19.
//

#ifndef SERVERPROJ2_SEARCHABLE_H
#define SERVERPROJ2_SEARCHABLE_H

#include <vector>
#include "State.h"

class Searchable {
public:
    virtual State* getInitialState() = 0;

    virtual State* getGoalState() = 0;

    virtual std::vector<State*> getAllPossibleStates(State*) = 0;
};


#endif //SERVERPROJ2_SEARCHABLE_H
