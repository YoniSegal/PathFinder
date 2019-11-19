//
// Created by oriel on 1/15/19.
//

#ifndef SERVERPROJ2_SEARCHABLEMATRIX1_H
#define SERVERPROJ2_SEARCHABLEMATRIX1_H

#include "Searchable.h"
#include <vector>
using std::vector;


class SearchableMatrix : public Searchable {
private:
    State *initialState;
    State *goalState;

public:
    vector<vector<State>> matrix;

    SearchableMatrix(std::vector<std::vector<int>> givenMatrix, std::pair<int, int> start, std::pair<int, int> end);

    State *getInitialState() override {
        return initialState;
    }

    State *getGoalState() override {
        return goalState;
    }

    std::vector<State *> getAllPossibleStates(State *state) override {
        return state->getNeighbors();
    }

};


#endif //SERVERPROJ2_SEARCHABLEMATRIX1_H
