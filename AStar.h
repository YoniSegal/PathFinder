//
// Created by yonisegal on 1/10/19.
//

#ifndef SERVERPROJ2_ASTAR_H
#define SERVERPROJ2_ASTAR_H

#include <queue>
#include <algorithm>
#include "Searcher.h"
#include "Util.h"

class AStar : public Searcher {

    inline int heuristic(State *a, State *b) {
        return std::abs((int) (a->row_index - b->row_index)) + std::abs(((int) (a->col_index - b->col_index)));
    }

private:
    Util::result result;

public:

    Util::result search(Searchable *searchable) override {

        result.developedVertex = 0;
        result.shortestPath = "";
        result.weight = 0;

        auto start = searchable->getInitialState();
        auto goal = searchable->getGoalState();


        std::map<State *, State *> came_from;

        std::map<State *, int> cost_so_far;


        PriorityQueue<State *, int> frontier;
        frontier.put(start, 0);

        came_from[start] = start;
        cost_so_far[start] = 0;

        State *current = NULL;

        while (!frontier.empty()) {
            current = frontier.get();


            if (current == goal) {
                break;
            }

            for (State *next : current->getNeighbors()) {
                if (next->isInfinity)
                    continue;
                int new_cost = cost_so_far[current] + next->weigth;
                if (cost_so_far.find(next) == cost_so_far.end()
                    || new_cost < cost_so_far[next]) {
                    cost_so_far[next] = new_cost;
                    int priority = new_cost + heuristic(next, goal);
                    frontier.put(next, priority);
                    came_from[next] = current;
                    result.developedVertex++;
                }
            }

        }

        std::vector<State *> path;

        if (current != goal) {
            result.shortestPath = "";
            result.weight = -1;
            return result;
        }


        while (current != start) {


            path.push_back(current);
            current = came_from[current];
            result.weight += current->weigth;
        }

        path.push_back(start);
        std::reverse(path.begin(), path.end());

        std::string step;

        auto it = path.begin();
        for (; it != path.end() && it + 1 != path.end(); it++) {

            if ((*(it + 1))->col_index > (*(it))->col_index) {
                step = "Right, ";
            }

            if ((*(it + 1))->col_index < (*(it))->col_index)
                step = "Left, ";

            if ((*(it + 1))->row_index > (*(it))->row_index)
                step = "Down, ";

            if ((*(it + 1))->row_index < (*(it))->row_index)
                step = "Up, ";

            result.shortestPath.append(step);

        }

        result.shortestPath =
                result.shortestPath.substr(0, result.shortestPath.length() - 2);


        return result;

    }
};

#endif //SERVERPROJ2_ASTAR_H
