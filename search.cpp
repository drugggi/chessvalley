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
    Bitboards evalBoard {charBoard, whitesTurn};
    eval = evalBoard.countMaterial() + evalBoard.countAttackingSquares(); 

}
Search::~Search() {
    counter--;
}
int Search::counter=0;
int Search::root=0;
//int Search::root2=0;

// when searching opponents turn, we assume that he/she makes the best possible move
void Search::sortResults(bool whitesTurn) {

    if (moveFrom == moveTo) {
        for (int i = 0; i < nextMoveSearch.size() ; i++) {
            nextMoveSearch.at(i).sortResults(!whitesTurn);
            // std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
        }
    }
    else if (nextMoveSearch.size() != 0) {
        for (int i = 0 ; i < nextMoveSearch.size() ; i++) {
            nextMoveSearch.at(i).sortResults(!whitesTurn);

            /*
            for (int j = 0 ; j < nextMoveSearch.size() ; j++) {
                std::cout << nextMoveSearch.at(j).getEval() << " ";
            }
            std::cout << "->";
            */
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
            /*
            for (int j = 0 ; j < nextMoveSearch.size() ; j++) {
                std::cout << nextMoveSearch.at(j).getEval() << " ";
            }
            std::cout << "\n";
            */
            //std::cout << "wT:(" << whitesTurn << ") ";
            /*
            if (whitesTurn) {
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
            } else {
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end(), std::greater<Search>() );
            }
            */
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
            /*
        float bestEval = nextMoveSearch.at(0).getEval();
        for (int i = 1; i < nextMoveSearch.size() ; i++) {
            float temp = nextMoveSearch.at(i).getEval();
           if (temp < bestEval) {
              bestEval = temp; 
           }
        }
        eval = bestEval;
        */
            // sorting just searched moves, and setting "base" eval to 
            // either best white's or black's move
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
            if (!whitesTurn) {
                eval = nextMoveSearch.at(0).getEval();
            } else {
                eval = nextMoveSearch.at(nextMoveSearch.size() - 1).getEval();
            }
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
void Search::sortRootEvals() {

    if (nextMoveSearch.size() != 0) {
        std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
    }
    /*
    for (int i = 0; i < nextMoveSearch.size()-1 ; i++ ) {
        for (int j = i+1 ; j < nextMoveSearch.size() ; j++) {

        if ( nextMoveSearch.at(i).getEval() < nextMoveSearch.at(j).getEval() ) {

            std::cout << "swapperoo" << "\n";
        std::swap(nextMoveSearch.at(i), nextMoveSearch.at(j) );
        }
        }

    }
    */

}
/*
const void Search::printTopTreeRoute() {

    if (moveFrom == moveTo) {
        root = 0;

        for (Search sr: nextMoveSearch) {
           root++;
            sr.printTopTreeRoute();
            root--;
        }

    }
    else {
    if (nextMoveSearch.size() != 0) {
        root++;
        if ( root % 2 == 1 ) {
        std::cout << Chessboard::coordinate(moveFrom) << "->" << Chessboard::coordinate(moveTo)
          << "  " ;
        nextMoveSearch.at(0).printTopTreeRoute();
        } else {

        std::cout << Chessboard::coordinate(moveFrom) << "->" << Chessboard::coordinate(moveTo)
          << "  " ;
        nextMoveSearch.at(nextMoveSearch.size() - 1).printTopTreeRoute();
        }
        root--;

    }
    else {
        std::cout << Chessboard::coordinate(moveFrom) << "->" << Chessboard::coordinate(moveTo)
          << "  " ;
        std::cout << "(" << eval<<")\n";
    }
    }
}
*/
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
        //root2 = 0;
    }
    if (nextMoveSearch.size() == 0 ) {
        return eval;
    }
    else {
        return nextMoveSearch.at(0).getEval();
        /*
        if ( root2 % 2 == 0 ) {
            root2++;
            return nextMoveSearch.at(0).getEval();
            root2--;
        }
        // best move from white is at the bottom
        else {
            root2++;
            return nextMoveSearch.at(nextMoveSearch.size() -1).getEval();
            root2--;
        }
        */
    }
}
const int Search::getMoveFrom() {
    if (moveFrom == moveTo) {
        return nextMoveSearch.at(0).getMoveFrom();
        //return nextMoveSearch.at(nextMoveSearch.size() - 1).getMoveFrom();

    }
    return moveFrom;
}
const int Search::getMoveTo() {
    if(moveFrom == moveTo) {
        return nextMoveSearch.at(0).getMoveTo();
        //return nextMoveSearch.at(nextMoveSearch.size() - 1).getMoveTo();
    }
    return moveTo;
}
/* void Search::sortLeafs() {

    if (moveFrom == moveTo) {

        for (Search ms: nextMoveSearch) {
            root++;
            ms.sortLeafs();
            root--;
        }
    }
    else {
        if (nextMoveSearch.size() == 0) {
            return;
        }
        else {
            for (int i = 0 ; i < nextMoveSearch.size() ; i++) {
                root++;
                nextMoveSearch.at(i).sortLeafs();
                root--;
                std::cout << "R("<<root<< " " << eval << ")";
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
            }
        }
    }
}
*/
const void Search::printSearchTree() {
    // root
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
