#include <iostream>
#include <vector>
#include <array>
#include "chessboard.h"
#include "bitboards.h"
#include "pieceinfo.h"
#include "search.h"

Search::Search(std::array<char, 64> charBoard, int from, int to,  bool whitesTurn) {
    charBoard[to] = charBoard[from];
    charBoard[from] = ' ';
    Bitboards evalBoard {charBoard, whitesTurn};


    eval = evalBoard.countMaterial() + evalBoard.countBlackAttackingSquares(); 

}
Search::~Search() {

}
std::array<char,64> Search::updateCharBoard(std::array<char,64> charBoard, int from, int to) {
    charBoard[to] = charBoard[from];
    charBoard[from] = ' ';
}

void Search::searchNextMoves(std::array<char,64> charBoard, bool whitesTurn) {
    
    if (nextMoveSearch.size() != 0) {
        std::cout << "Searching beyond next moves starts" << "\n";
        for (int i = 0; i < nextMoveSearch.size() ; i++) {
           
            int from = nextMoveSearch.at(i).getMoveFrom();
            int to = nextMoveSearch.at(i).getMoveTo();
            std::array<char,64> temp = updateCharBoard(charBoard, from, to);
            std::cout << "searchnextmovesnext\n";
            nextMoveSearch.at(i).searchNextMoves(temp, !whitesTurn);
            std::cout << "searchnextmoveStops\n";
            //nextMoveSearch.at(i).searchNextMoves(charBoard
            // if size != search one node deeper
        }
    }
    // std::cout << "next level search starts!" << "\n";

    std::cout << "trying to create bitboard\n";
    Bitboards currentBoard {charBoard, whitesTurn};
 //   std::cout << "bitboard created\n";
    std::vector<PieceInfo> blackPieces = currentBoard.getBlackPieces();
   // std::cout <<"bitboard created and blackpieces retrieved\n";
    
    std::vector<int> moves;
    int pieceFrom;
    int pieceTo;
    float bestEval=100;
    for (int i = 0; i < blackPieces.size() ; i++) {

        if (blackPieces.at(i).getLegalMoves().any() ) {
            moves = blackPieces.at(i).getLegalMoveSquares();
            pieceFrom = blackPieces.at(i).getSquare();

            for (int j = 0; j < moves.size() ; j++) {
                pieceTo = moves.at(j);
                Search temp {charBoard, pieceFrom, pieceTo, whitesTurn};
                nextMoveSearch.push_back(temp);

            }

        }
    }
//    std::cout <<pieceFrom <<  "next level searching ends" << pieceTo <<  "\n";


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
    return moveFrom;
}
int Search::getMoveTo() {
    return moveTo;
}
