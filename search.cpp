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

    counter++;
    Bitboards evalBoard {charBoard, whitesTurn};
    eval = evalBoard.countMaterial() + evalBoard.countAttackingSquares(); 

}
Search::~Search() {

    //counter--;
}
int Search::counter=0;
int Search::root=0;
int Search::root2=0;

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

            for (int j = 0 ; j < nextMoveSearch.size() ; j++) {
                std::cout << nextMoveSearch.at(j).getEval() << " ";
            }
            std::cout << "->";
            std::sort(nextMoveSearch.begin(), nextMoveSearch.end() );
            for (int j = 0 ; j < nextMoveSearch.size() ; j++) {
                std::cout << nextMoveSearch.at(j).getEval() << " ";
            }
            std::cout << "\n";
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
void Search::sortRootEvals() {

    for (int i = 0; i < nextMoveSearch.size()-1 ; i++ ) {
        for (int j = i+1 ; j < nextMoveSearch.size() ; j++) {

        if ( nextMoveSearch.at(i).getEval() > nextMoveSearch.at(j).getEval() ) {

    //        std::cout << "swapperoo" << "\n";
        std::swap(nextMoveSearch.at(i), nextMoveSearch.at(j) );
        }
        }

    }

}
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
        if ( root % 2 == 0 ) {
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
const float Search::getEval() {
    if (moveFrom == moveTo) {
        root2 = 0;
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
void Search::sortLeafs() {

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
const void Search::printSearchTree() {
    // root
    if (moveFrom == moveTo ) {
        
        for (Search ms: nextMoveSearch) {
            std::cout << "   next root move:" << "\n";
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
            <<Chessboard::coordinate(moveTo) << "  "; 
            }
            else {

                for (int j = 0; j < root ; j++) {
                std::cout << "        ";
                }
            }
            root++;
            nextMoveSearch.at(i).printSearchTree();
            root--;
        }
    }
}
}
