#ifndef SEARCH_H
#define SEARCH_H

#include <array>
#include <vector>
#include "bitboards.h"

class Search {
    private:
        Bitboards *evalBoard;
        int moveFrom;
        int moveTo;
        float eval;
        std::vector<Search> nextMoveSearch;
    public:
        Search(std::array<char,64> charBoard, bool whitesTurn);
        ~Search();
        void evaluateCurrentBoard(std::array<char,64> SQ,bool whitesTurn);
        void searchNextMoves(std::array<char,64> charBoard, bool whitesTurn);
        float getEval();
        int getMoveFrom();
        int getMoveTo();
        std::array<char,64> updateCharBoard(std::array<char,64> charBoard, int from, int to);
};


#endif
