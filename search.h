#ifndef SEARCH_H
#define SEARCH_H

#include <array>
#include <vector>

class Search {
    private:
        int move;
        float eval;
        std::vector<Search> nextMoveSearch;
    public:
        Search();
        ~Search();
        void searchNextMoves();
        float getEval();
};


#endif
