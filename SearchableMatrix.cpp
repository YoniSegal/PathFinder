//
// Created by yonisegal on 1/10/19.
//

#ifndef SERVERPROJ2_SEARCHABLEMATRIX_H
#define SERVERPROJ2_SEARCHABLEMATRIX_H

#include "SearchableMatrix.h"

SearchableMatrix::SearchableMatrix(std::vector<std::vector<int>> recievedMatrix, std::pair<int, int> start,
                                       std::pair<int, int> end) : matrix(recievedMatrix.size(),
                                                                         std::vector<State>(recievedMatrix[0].size(), State(0))) {

    unsigned int rowSize = recievedMatrix.size();
    unsigned int colSize = recievedMatrix[0].size();

    //building the basic matrix
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            int currentWeigth = recievedMatrix[i][j];
            matrix[i][j].weigth = currentWeigth;
        }
    }

    //init all the state with values
    for (int i = 0; i < rowSize; ++i) {

        for (int j = 0; j < colSize; ++j) {

            State *curState = &matrix[i][j];

            curState->gotFrom = NotSet;

            curState->isMarked = false;

            curState->isInfinity = curState->weigth == -1 ? true : false;

            curState->top = i != 0 ? &matrix[i - 1][j] : NULL;

            curState->bottom = i != (rowSize - 1) ? &matrix[i + 1][j] : NULL;

            curState->left = j != 0 ? &matrix[i][j - 1] : NULL;

            curState->right = j != (colSize - 1) ? &matrix[i][j + 1] : NULL;

            curState->row_index = i;
            curState->col_index = j;


            if (i == start.first && j == start.second) {
                initialState = &matrix[i][j];
            }

            if (i == end.first && j == end.second) {
                goalState = &matrix[i][j];
            }

        }

    }
}


#endif //SERVERPROJ2_SEARCHABLEMATRIX_H
