#ifndef SEARCH_H
#define SEARCH_H

#include <array>
#include <vector>

class Search {
    private:
        std::array<char,64> currentBoard;
        std::vector<int> legalMoves;
        // best move
        int moveFrom;
        int moveTo;

    public:
        Search(std::array<char,64> charBoard, bool whiteToMove);
        ~Search();
        int getMoveFrom();
        int getMoveTo();
};


#endif
