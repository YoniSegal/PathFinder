//
// Created by yonisegal on 1/10/19.
//

#include "Searchable.h"
#include <algorithm>
#include <queue>
#include "State.h"
#include <map>
#ifndef SERVERPROJ2_SEARCHER_H
#define SERVERPROJ2_SEARCHER_H


class Searcher {
public:
    virtual Util::result search(Searchable* searchable) = 0;

    virtual ~Searcher() {

    }
};

template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
            std::greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

#endif //SERVERPROJ2_SEARCHER_H
