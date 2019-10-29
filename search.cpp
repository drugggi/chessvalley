#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include "chessboard.h"
#include "bitboards.h"
#include "pieceinfo.h"
#include "search.h"

Search::Search(std::array<char,64> charBoard, bool whitesTurn) {
    Bitboards evalBoard{charBoard, whitesTurn};
    eval = evalBoard.countMaterial() + evalBoard.countAttackingSquares();

    //this means that no move is searched yet
    moveFrom = 0;
    moveTo = 0;
    std::cout << "back to square 1: eval : " << eval << "\n";
}

Search::Search(std::array<char, 64> charBoard,int from, int to, bool whitesTurn) {
    /*
    for (int i = 0 ; i < charBoard.size() ; i++) {
        std::cout << charBoard[i];
    }
    std::cout << "\n";
    */
    updateCharBoard(&charBoard,from , to);
    /*
    for (int i = 0 ; i < charBoard.size() ; i++) {
        std::cout << charBoard[i];
    }
    */
    moveFrom = from;
    moveTo = to;

    Bitboards evalBoard {charBoard, whitesTurn};
    eval = evalBoard.countMaterial() + evalBoard.countAttackingSquares(); 

}
Search::~Search() {

}
void Search::sortResults() {

    if (nextMoveSearch.size() != 0) {

        for (int i = 0 ; i < nextMoveSearch.size() ; i++) {

            nextMoveSearch.at(i).sortResults();
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
        }

        //sortResults();
        //std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
        //eval = nextMoveSearch.at(0).getEval();
        return;

    }
    else {

        return;
    
    }
}
void Search::searchNextMoves(std::array<char,64> charBoard, bool whitesTurn) {

    updateCharBoard(&charBoard,moveFrom, moveTo);
    // Bitboards evalBoard{charBoard, whitesTurn};
    if ( nextMoveSearch.size() != 0 ) {
  //      std::cout << "nextmoves already searched! should we go deeper? "<< "\n";
        
        //nextMoveSearch.at(0).searchNextMoves(charBoard, !whitesTurn);
        for (int i = 0 ; i < nextMoveSearch.size() ; i++) {
        
        nextMoveSearch.at(i).searchNextMoves(charBoard, !whitesTurn);
        }
/*
        for (Search ms: nextMoveSearch) {
            ms.printSearchInfo();
        }
        */
        
    }
    else {
        Bitboards evalBoard{charBoard, whitesTurn};
        std::vector<std::pair<int,int> > allMoves = evalBoard.getLegalMoves(whitesTurn);
        
 //       std::cout << "nextmovessearch.size() == 0, should do some searching!" << "\n";
        for (auto pair: allMoves) {
            Search nextMove{charBoard, pair.first, pair.second, whitesTurn};
            nextMoveSearch.push_back(nextMove);
        }
        // std::sort(nextMoveSearch.begin() , nextMoveSearch.end() );
    }


}
const void Search::printSearchInfo() {
    if (nextMoveSearch.size() == 0) {
    std::cout << Chessboard::coordinate(moveFrom) << "->" << Chessboard::coordinate(moveTo) << "(" << eval << ")  ";
    }
    else {
        std::cout << "nextMoveSearched! print deeper from move:" << Chessboard::coordinate(moveFrom)
            << "->" << Chessboard::coordinate(moveTo) << "\n";
        for(Search ms: nextMoveSearch) {
            ms.printSearchInfo();
        }
        std::cout << "\n deep printing done:" << moveFrom << "->" << moveTo << "\n";
    }
}
const void Search::printMoveEvals() {
    if (moveFrom != 0 && moveTo != 0) {
        std::cout << Chessboard::coordinate(moveFrom) << "->" 
            <<Chessboard::coordinate(moveTo) << "  "; 
    }
    if (nextMoveSearch.size() == 0) {
        std::cout << "(" << eval<<")\n";
    }
    else {
        for (Search ms: nextMoveSearch) {
            ms.printMoveEvals();
        }
    }

}
const void Search::printBestEval() {

        for (Search ms: nextMoveSearch) {
            std::cout << ms.getEval() << "\n";
        }


}
void Search::updateCharBoard(std::array<char,64> *charBoard, int from, int to) {
    // there is no move made in root node (initial position for example starting position)
    if (from == to ) {return; }
    charBoard->at(to) = charBoard->at(from);
    charBoard->at(from) = ' ';

    if (charBoard->at(to) == 'P' && to < 8) {
        std::cout << "automatic promotion, change this in future\n";
        charBoard->at(to) = 'Q';
    }
    else  if ( charBoard->at(to) == 'p' && to > 55 ) {
       charBoard->at(to) = 'q';
    } 
}
float Search::getEval() {
    if (nextMoveSearch.size() == 0 ) {
        return eval;
    }
    else {
        return nextMoveSearch.at(0).getEval();
    }
}
int Search::getMoveFrom() {
    if (moveFrom == moveTo) {
        return nextMoveSearch.at(0).getMoveFrom();

    }
    return moveFrom;
}
int Search::getMoveTo() {
    if(moveFrom == moveTo) {
        return nextMoveSearch.at(0).getMoveTo();
    }
    return moveTo;
}
