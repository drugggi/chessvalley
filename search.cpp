#include <iostream>
#include <vector>
#include <array>
#include "chessboard.h"
#include "bitboards.h"
#include "pieceinfo.h"
#include "search.h"

Search::Search(std::array<char,64> charBoard, bool whiteToMove) {
    std::cout << "searching started!" << "\n";

    currentBoard = charBoard;
    Bitboards currentBoard {charBoard, whiteToMove};
    std::vector<PieceInfo> blackPieces = currentBoard.getBlackPieces();
    
    std::vector<int> moves;
    int startingSquare;
    char movingPiece;
    float bestEval=100;
    for (int i = 0 ; i < blackPieces.size() ; i++) {
        if (blackPieces.at(i).getLegalMoves().any() ) {
            moves = blackPieces.at(i).getLegalMoveSquares();
                
            std::cout << "\n"<< blackPieces.at(i).getPiece() << "(" <<
                Chessboard::coordinate(blackPieces.at(i).getSquare() ) << ")";
            movingPiece = blackPieces.at(i).getPiece();
            startingSquare = blackPieces.at(i).getSquare();
            // test moves from starting square to legal squares found in moves
            for (int j = 0 ; j < moves.size() ; j++) {
                charBoard[startingSquare] = ' ';
                char tempPiece = charBoard[moves.at(j) ];
                charBoard[moves.at(j) ] = movingPiece;

                Bitboards evalBoard {charBoard, !whiteToMove};
                float eval = evalBoard.countMaterial();
                float attackingSquares = evalBoard.countBlackAttackingSquares();
               /* 
                 std::cout <<blackPieces.at(i).getPiece() << Chessboard::coordinate(moves.at(j) )
                     << " c: " << eval  << " ba: " << attackingSquares << " wa: " << evalBoard.countWhiteAttackingSquares() << " ";
                     */

                 eval += attackingSquares;
                 std::cout << Chessboard::coordinate(moves.at(j) ) << ":(" << eval << ") ";
                if (eval < bestEval) {
                    std::cout << " bestEval ";
                    bestEval = eval;
                    moveFrom = startingSquare;
                    moveTo = moves.at(j);
                }
                charBoard[startingSquare] = movingPiece;
                charBoard[moves.at(j) ] = tempPiece;

            }
        }
    }


}
int Search::getMoveFrom() {
    return moveFrom;
}
int Search::getMoveTo() {
    return moveTo;
}
Search::~Search() {

}
