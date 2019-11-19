

#ifndef SERVERPROJ2_SOLVER_H
#define SERVERPROJ2_SOLVER_H

namespace server_side {

    template<class P, class S>

    class Solver {

    public:

        virtual S solve(P) = 0;

        virtual ~Solver() = default;
    };
}

#endif //SERVERPROJ2_SOLVER_H
