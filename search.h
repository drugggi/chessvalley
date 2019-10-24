#ifndef SEARCH_H
#define SEARCH_H

#include <array>

class Search {
    private:
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
