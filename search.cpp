#include <iostream>
#include <vector>
#include <array>
#include "chessboard.h"
#include "bitboards.h"
#include "pieceinfo.h"
#include "search.h"

Search::Search(std::array<char, 64> charBoard, bool whitesTurn) {

    evalBoard = new Bitboards{charBoard, whitesTurn};
    eval = evalBoard->countMaterial() + evalBoard->countAttackingSquares(); 

    std::cout << "back to square 1: eval: " << eval << "\n";

}
Search::~Search() {

    delete evalBoard;
}
void Search::evaluateCurrentBoard(std::array<char,64> SQ,bool whitesTurn) {

    std::vector<PieceInfo> blackPieces = evalBoard->getBlackPieces();

    std::array<int,3> moveEval;
    std::vector<std::array<int,3> > allMoveEvals;
    std::vector<int> moves;

    for (int i = 0 ; i < blackPieces.size() ; i++) {
        if (blackPieces.at(i).getLegalMoves().any() ) {
            moves = blackPieces.at(i).getLegalMoveSquares();
                
            std::cout << "\n"<< blackPieces.at(i).getPiece() << "(" <<
                Chessboard::coordinate(blackPieces.at(i).getSquare() ) << ") -> ";
            char movingPiece = blackPieces.at(i).getPiece();
            moveEval[0] = blackPieces.at(i).getSquare();
            // test moves from starting square to legal squares found in moves
            for (int j = 0 ; j < moves.size() ; j++) {
                SQ[moveEval[0] ] = ' ';
                char tempPiece = SQ[moves.at(j) ];
                SQ[moves.at(j) ] = movingPiece;

                moveEval[1] = moves.at(j);
                Bitboards tempBoard {SQ, !whitesTurn};
               float tempEval = tempBoard.countMaterial() + tempBoard.countAttackingSquares(); 
               moveEval[2] = 100*tempEval;
    
               allMoveEvals.push_back(moveEval);
                 std::cout << Chessboard::coordinate(moves.at(j) ) << ":(" << tempEval << ") ";
 /*               if (tempEval < bestEval) {
                    std::cout << " bestEval ";
                    bestEval = tempEval;
                    moveFrom = startingSquare;
                    moveTo = moves.at(j);
                }
                */
                SQ[moveEval[0] ] = movingPiece;
                SQ[moves.at(j) ] = tempPiece;

            }
        }
    }
    for (auto m : allMoveEvals) {

        std::cout << m[0] << " " << m[1] << " " << m[2] << "\n";
    }

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
                Search temp {charBoard, whitesTurn};
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
