//
// Created by oriel on 1/13/19.
//

#ifndef SERVERPROJ2_SOLVERTOSEARCHER_H
#define SERVERPROJ2_SOLVERTOSEARCHER_H

// OBJECT ADAPTER

#include "Util.h"
#include "Solver.h"
#include "Searcher.h"

class SolverToSearcher : public server_side::Solver<Searchable *, Util::result> {

    Searcher *searcher;

public:

    SolverToSearcher(Searcher *searcher) : searcher(searcher) {}

    Util::result solve(Searchable *p) override {
        return searcher->search(p);
    }

    ~SolverToSearcher() override {
        delete(searcher);
    }

};


#endif //SERVERPROJ2_SOLVERTOSEARCHER_H
