#ifndef SEARCH_H
#define SEARCH_H

#include <array>
#include <vector>
#include "bitboards.h"

class Search {
    private:
        int moveFrom;
        int moveTo;
        float eval;
        std::vector<Search> nextMoveSearch;
    public:
        Search(std::array<char,64> charBoard, bool whitesTurn);
        Search(std::array<char,64> charBoard,int from, int to, bool whitesTurn);
        ~Search();
        void searchNextMoves(std::array<char,64> charBoard, bool whitesTurn);
        float getEval();
        int getMoveFrom();
        int getMoveTo();
        void updateCharBoard(std::array<char,64> *charBoard, int from, int to);
        const void printSearchInfo();
        const void printMoveEvals();
};


#endif
