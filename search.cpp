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
    counter++;
    std::cout << "back to square 1: eval : " << eval << "\n";
}

// One Search represents a chess move, whis is made in charBoard
Search::Search(std::array<char, 64> charBoard,int from, int to, bool whitesTurn) {
    updateCharBoard(&charBoard,from , to);
    moveFrom = from;
    moveTo = to;

    counter++;
    // with Bitboards we get legal moves and some intelligence
    // consider using new class evaluate.cpp and using bitboards only when searching new moves
    Bitboards evalBoard {charBoard, whitesTurn};
    eval = evalBoard.countMaterial() + evalBoard.countAttackingSquares(); 

}
Search::~Search() {
}
int Search::counter=0;
int Search::root=0;

// when searching opponents turn, we assume that he/she makes the best possible move
void Search::sortResults(bool whitesTurn) {

    if (moveFrom == moveTo) {
        for (int i = 0; i < nextMoveSearch.size() ; i++) {
            nextMoveSearch.at(i).sortResults(!whitesTurn);
        }
    }
    else if (nextMoveSearch.size() != 0) {
        for (int i = 0 ; i < nextMoveSearch.size() ; i++) {
            nextMoveSearch.at(i).sortResults(!whitesTurn);
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
        }
    }
    else {
        // just return when end of search tree, nothing to sort
        return;
    }
}
void Search::searchNextMoves(std::array<char,64> charBoard, bool whitesTurn) {

    // calling this method again and again we have to update board repreentation
    updateCharBoard(&charBoard,moveFrom, moveTo);
    // Bitboards evalBoard{charBoard, whitesTurn};
    if ( nextMoveSearch.size() != 0 ) {
        for (int i = 0 ; i < nextMoveSearch.size() ; i++) {
        nextMoveSearch.at(i).searchNextMoves(charBoard, !whitesTurn);
        }
    }
    else {
        // getting all the legal moves and searching them
        Bitboards evalBoard{charBoard, whitesTurn};
        std::vector<std::pair<int,int> > allMoves = evalBoard.getLegalMoves(whitesTurn);
        for (auto pair: allMoves) {
            Search nextMove{charBoard, pair.first, pair.second, whitesTurn};
            nextMoveSearch.push_back(nextMove);
        }
        
        if (nextMoveSearch.size() != 0) {
            // sorting just searched moves, and setting "base" eval to 
            // either best white's or black's move
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
            if (!whitesTurn) {
                eval = nextMoveSearch.at(0).getEval();
            } else {
                eval = nextMoveSearch.at(nextMoveSearch.size() - 1).getEval();
            }
        }
    }


}
void Search::searchNextMovesIntelligently(std::array<char,64> charBoard, bool whitesTurn) {

    // calling this method again and again we have to update board repreentation
    updateCharBoard(&charBoard,moveFrom, moveTo);
    // Bitboards evalBoard{charBoard, whitesTurn};
    if ( nextMoveSearch.size() != 0 ) {
        for (int i = 0 ; i < nextMoveSearch.size() ; i++) {
            nextMoveSearch.at(i).searchNextMoves(charBoard, !whitesTurn);
            //if ( i > 1 ) { std::cout << "break! " << "\n"; break; }
        }
    }
    else {
        // getting all the legal moves and searching them
        Bitboards evalBoard{charBoard, whitesTurn};
        std::vector<std::pair<int,int> > allMoves = evalBoard.getLegalMoves(whitesTurn);
        for (auto pair: allMoves) {
            Search nextMove{charBoard, pair.first, pair.second, whitesTurn};
            nextMoveSearch.push_back(nextMove);
        }
        
        if (nextMoveSearch.size() != 0) {
            // sorting just searched moves, and setting "base" eval to 
            // either best white's or black's move
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
            if (!whitesTurn) {
                eval = nextMoveSearch.at(0).getEval();
            } else {
                eval = nextMoveSearch.at(nextMoveSearch.size() - 1).getEval();
            }
        }
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
void Search::sortRootEvals() {

    if (nextMoveSearch.size() != 0) {
        std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
    }

}

const void Search::printBestEval() {

    float bestEval = nextMoveSearch.at(0).getEval();
        for (Search ms: nextMoveSearch) {
            std::cout << ms.getEval() << " ";
            if (ms.getEval() < bestEval) {
                bestEval = ms.getEval();
            }
        }
            std::cout <<"bestEval: " << bestEval << "\n";


}
const void Search::printBaseEvals() {

    for (Search sh: nextMoveSearch) {
        std::cout << Chessboard::coordinate(sh.getMoveFrom() ) << "->" << 
            Chessboard::coordinate(sh.getMoveTo() ) << "(" << sh.getRealEval() << ")  ";
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
const float Search::getRealEval() {
    return eval;
}
const float Search::getEval() {
    if (moveFrom == moveTo) {
    }
    if (nextMoveSearch.size() == 0 ) {
        return eval;
    }
    else {
        return nextMoveSearch.at(0).getEval();
    }
}
const int Search::getMoveFrom() {
    if (moveFrom == moveTo) {
        return nextMoveSearch.at(0).getMoveFrom();

    }
    return moveFrom;
}
const int Search::getMoveTo() {
    if(moveFrom == moveTo) {
        return nextMoveSearch.at(0).getMoveTo();
    }
    return moveTo;
}

const void Search::printSearchTree() {
    if (moveFrom == moveTo ) {
        
        for (Search ms: nextMoveSearch) {
            std::cout << "   next root move: this eval: "<< eval << "\n";
            root++;
            ms.printSearchTree();
            root--;
        }
    }
    else {    
    if (nextMoveSearch.size() == 0) {
        std::cout << Chessboard::coordinate(moveFrom) << "->" 
            <<Chessboard::coordinate(moveTo) << "  " << "(" << eval<<")\n";
    }
    else {
        for (int i = 0; i < nextMoveSearch.size() ; i++) {
            if (i == 0) {
            
        std::cout << Chessboard::coordinate(moveFrom) << "->" 
            <<Chessboard::coordinate(moveTo) << " ("<< eval << ") "; 
            }
            else {

                for (int j = 0; j < root ; j++) {
                std::cout << "               ";
                }
            }
            root++;
            nextMoveSearch.at(i).printSearchTree();
            root--;
        }
    }
}
}
