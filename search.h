#ifndef SEARCH_H
#define SEARCH_H

#include <array>
#include <vector>
#include "bitboards.h"

class Search {
    private:
        int moveFrom=0;
        int moveTo=0;
        float eval;
        std::vector<Search> nextMoveSearch;
    public:
        static int counter;
        static int root;
 //       static int root2;
        Search(std::array<char,64> charBoard, bool whitesTurn);
        Search(std::array<char,64> charBoard,int from, int to, bool whitesTurn);
        ~Search();
        void searchNextMoves(std::array<char,64> charBoard, bool whitesTurn);
        void searchNextMovesIntelligently(std::array<char,64> charBoard, bool whitesTurn);
        const float getEval();
        const float getRealEval();
        const int getMoveFrom();
        const int getMoveTo();
        void updateCharBoard(std::array<char,64> *charBoard, int from, int to);
        const void printSearchInfo();
        const void printMoveEvals();
        const void printBestEval();
        const void printSearchTree();
        const void printTopTreeRoute();
        const void printBaseEvals();
        //void sortLeafs();
        void sortResults(bool whitesTurn);
        void sortRootEvals();
        bool operator < (const Search& sh) const {
            return (eval < sh.eval );
        }
        bool operator > (const Search& sh) const {
            return (eval > sh.eval );
        }
};


#endif
