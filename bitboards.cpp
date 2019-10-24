#include <bitset>
#include <iostream>
#include <array>
#include <vector>
#include "bitboards.h"
#include "pieceinfo.h"
#include "chessboard.h"

Bitboards::Bitboards(std::vector<PieceInfo> wpPI, std::vector<PieceInfo> bpPI, bool whiteToMove) {

    if (whiteToMove) {
        std::cout << "new bitboards constructor, white to move" << "\n";
    } else {
        std::cout << "new bitboard constructor, black to move" << "\n";
    }

}

Bitboards::Bitboards(std::array<char,64> pieceBoard, bool whiteToMove) {
    charBoard = pieceBoard;
/*    
    if(whiteToMove) {
        std::cout << "it is white's turn" << "\n";
    } else {
        std::cout << "it is black's turn" << "\n";
    }
*/
    // create bitboards for white/blac pieces from char board
    for (int i = 0; i < 64 ; i++ ) {
        whitePieces[i] = 0;
        blackPieces[i] = 0;
        occupiedSquares[i] = 0;
        // each square is either empty or has black/white piece
        if (pieceBoard.at(i) != ' ') {
            if ((int) pieceBoard.at(i) < ((int)'a') ) {
               whitePieces[i] = 1;
               }
            else {
               blackPieces[i] = 1;
            } 
            occupiedSquares[i] = 1;
        }
    }
    // get attacking moves, which helps to get legal moves when king is in check
    for (int i = 0 ; i < pieceBoard.size() ; i++) {
        if (pieceBoard.at(i) != ' ') {
            PieceInfo temp {pieceBoard.at(i) , i };
            if ((int)pieceBoard.at(i) < (int)'a') {
               // whiteAttacking = whiteAttacking |= getAttackingMoves(i,pieceBoard.at(i) );
               temp.setLegalMoves( getAttackingMoves(i,pieceBoard.at(i) ) );
               whitePiecesPI.push_back(temp);
            }
            else {
               // blackAttacking = blackAttacking |= getAttackingMoves(i,pieceBoard.at(i) );
                temp.setLegalMoves( getAttackingMoves(i,pieceBoard.at(i) ) );
                blackPiecesPI.push_back(temp);
            }
        }
       
    }
//    std::cout << "white to move: " << whiteToMove << "\n";
    if (whiteToMove) {
        // create bitboards for whitePieces and blackPieces 
        std::bitset<64> tempPiecemoves;
        for (int j = 0 ; j < whitePiecesPI.size() ; j++) {
            tempPiecemoves = whitePiecesPI.at(j).getLegalMoves();

            // this goes through all 64 squares, optimize this please
            for (int i = 0 ; i < tempPiecemoves.size() ; i++ ) {

                // for every move there is, check if your own king is in check thus
                // making the move illegal 
                if (tempPiecemoves[i] == 1 ) {

                    char piecemoving = whitePiecesPI.at(j).getPiece();
                    int startingSquare = whitePiecesPI.at(j).getSquare();
                    char temppiece = charBoard[i];
                    whitePiecesPI.at(j).setSquare(i);
                    charBoard[startingSquare] = ' ';
                    charBoard[i]=piecemoving;

                    whitePieces[startingSquare] = 0;
                    whitePieces[i] = 1;
                   if (isWhiteKingInCheck() ) {
                      tempPiecemoves[i] = 0;
                      whitePiecesPI.at(j).setLegalMove(i, false);
                   }
                   whitePieces[startingSquare] = 1;
                   whitePieces[i] = 0;
                   whitePiecesPI.at(j).setSquare(startingSquare);
                   charBoard[startingSquare] = piecemoving;
                   charBoard[i] = temppiece;

                }

                
            }
        }

    }
    else { // black to move
        // create bitboards for whitePieces and blackPieces 
        std::bitset<64> tempPiecemoves;
        for (int j = 0 ; j < blackPiecesPI.size() ; j++) {
            tempPiecemoves = blackPiecesPI.at(j).getLegalMoves();

            // this goes through all 64 squares, optimize this please
            for (int i = 0 ; i < tempPiecemoves.size() ; i++ ) {

                // for every move there is, check if your own king is in check thus
                // making the move illegal 
                if (tempPiecemoves[i] == 1 ) {

                    char piecemoving = blackPiecesPI.at(j).getPiece();
                    int startingSquare = blackPiecesPI.at(j).getSquare();
                    char temppiece = charBoard[i];
                    blackPiecesPI.at(j).setSquare(i);
                    charBoard[startingSquare] = ' ';
                    charBoard[i]=piecemoving;

                    blackPieces[startingSquare] = 0;
                    blackPieces[i] = 1;
                   if (isBlackKingInCheck() ) {
                      tempPiecemoves[i] = 0;
                      blackPiecesPI.at(j).setLegalMove(i, false);
                   }
                   blackPieces[startingSquare] = 1;
                   blackPieces[i] = 0;
                   blackPiecesPI.at(j).setSquare(startingSquare);
                   charBoard[startingSquare] = piecemoving;
                   charBoard[i] = temppiece;

                }

                
            }
        }

    }
    std::bitset<64> tempLegalmoves;
    if (whiteToMove) {
    for (int i = 0; i < whitePiecesPI.size() ; i++  ) {
        tempLegalmoves = tempLegalmoves |= whitePiecesPI.at(i).getLegalMoves();
//        whitePiecesPI.at(i).printPieceInfo();
    }
    std::cout <<"\n";
    } else {
    for (int i = 0; i < blackPiecesPI.size() ; i++) {
        tempLegalmoves = tempLegalmoves |= blackPiecesPI.at(i).getLegalMoves();
 //       blackPiecesPI.at(i).printPieceInfo();
    }
    std::cout << "\n";
    }
  //  printBitboard(tempLegalmoves);
    if ( tempLegalmoves.any() == false ) {
        std::cout << "no legal moves" << "\n";
    
        if ( isBlackKingInCheck() ||isWhiteKingInCheck() ) {
            std::cout << " and king in check" << "\n";
         }
        std::string eof;
        std::cout << "press anything to crash the chessvalley"  << "\n";
        std::cin >> eof;
    }
}
std::vector<PieceInfo> Bitboards::getWhitePieces() {
    return whitePiecesPI;
}
std::vector<PieceInfo> Bitboards::getBlackPieces() {
    return blackPiecesPI;
}
const float Bitboards::countAttackingSquares() {
    return countWhiteAttackingSquares() - countBlackAttackingSquares();
}
const float Bitboards::countBlackAttackingSquares() {

    std::bitset<64> blackAttacking;
    for (int i = 0 ; i < blackPiecesPI.size() ; i++) {
        blackAttacking = blackAttacking |= blackPiecesPI.at(i).getLegalMoves();
    }
    return -(float)blackAttacking.count()/100;
}
const float Bitboards::countWhiteAttackingSquares() {

    std::bitset<64> whiteAttacking;
    for (int i = 0 ; i < whitePiecesPI.size() ; i++) {
        whiteAttacking = whiteAttacking |= whitePiecesPI.at(i).getLegalMoves();
    }
    return (float)whiteAttacking.count()/100;
}

const float Bitboards::countMaterial() {
    return countWhiteMaterial() - countBlackMaterial();
}
const float Bitboards::countBlackMaterial() {
    float value = 0;
    for (int i = 0 ; i < blackPiecesPI.size() ; i++) {
        value += blackPiecesPI.at(i).getValue();
    }
    return value;
}
const float Bitboards::countWhiteMaterial() {
    float value = 0;
    for (int i = 0 ; i < whitePiecesPI.size() ; i++) {
        value += whitePiecesPI.at(i).getValue();
    }
    return value;
}
bool Bitboards::isBlackKingInCheck() {


    int square;
    for (auto p : blackPiecesPI ) {
        if (p.getPiece() == 'k' ) {
            square = p.getSquare();
            break;
        }

    }
    int file = square % 8;
    int rank = square / 8;
    // lets check rook like moves and if there is white rook or queen there 
    for (int i = file+1 ; i < 8 ; i++ ) {
        if (charBoard[rank*8+i] != ' ') {
            if (charBoard[rank*8+i] == 'R' ||charBoard[rank*8+i] == 'Q') {
                return true;
            }
            else {
                break;
            }
        }
    }
    // look to the left
    for (int i = file - 1 ; i >= 0 ; i-- ) {
        if (charBoard[rank*8+i] != ' ') {
            if (charBoard[rank*8+i] == 'R'||charBoard[rank*8+i] == 'Q') {
                return true;
            }
            else {
                break;
            }
        }
    }

    // look down
    for (int i = rank + 1 ; i < 8 ; i++ ) {
        if (charBoard[i*8+file] != ' ') {
            if (charBoard[i*8+file] == 'R' ||charBoard[i*8+file] == 'Q') {
                return true;
            }
            else {
                break;
            }
        
        }
    }
    // look up
    for (int i = rank - 1 ; i >= 0 ; i-- ) {
        if (charBoard[i*8+file] != ' ') {
            if (charBoard[i*8+file] == 'R' ||charBoard[i*8+file] == 'Q') {
                return true;
            }
            else {
                break;
            }
        
        }
    }
    // lets check white knight checks
    rank = rank - 2;
    file++;
    if (rank >= 0 && file < 8 && charBoard[rank*8+file] == 'N') {
        return true;
    }
    rank++; file++;
    if (rank >= 0 && file < 8 && charBoard[rank*8+file] == 'N') {
        return true;
    }
    rank++; rank++;
    if (rank < 8 && file < 8 && charBoard[rank*8+file] == 'N') {
        return true;
    }
    rank++;file--;
    if (rank < 8 && file < 8 && charBoard[rank*8+file] == 'N') {
        return true;
    }
    // Knight moves to left clockwise still
    file--;file--;
    if (rank < 8 && file >= 0 && charBoard[rank*8+file] == 'N') {
        return true;
    }
    rank--;file--;
    if (rank < 8 && file >= 0 && charBoard[rank*8+file] == 'N') {
        return true;
    }
    rank--;rank--;
    if (rank >= 0 && file >= 0 && charBoard[rank*8+file] == 'N') {
        return true; 
    }
    rank--;file++;
    if (rank >= 0 && file >= 0 && charBoard[rank*8+file] == 'N') {
        return true; 
    }
    file = square % 8;
    int fileR = square % 8;
    int fileL = square % 8;
    rank = square / 8;
    bool clearR = true;
    bool clearL = true;
    // bishop moves down (rankn number goes up) one rank at a time 
    for (int i = rank+1; i < 8 ; i++ ) {
       fileR++;
       // At every rank look one file to right
       if (fileR < 8 && clearR) {
           // if there is own/white piece can't move there
           if (charBoard[i*8+fileR] == 'B' ||charBoard[i*8+fileR] == 'Q') {
               return true;
           }
           if (charBoard[i*8+fileR] != ' ') {
               clearR = false;
           }
       }
       fileL--;
       // bishop moves down and left
       if (fileL >= 0 && clearL) {
           if (charBoard[i*8+fileL] == 'B' ||charBoard[i*8+fileL] == 'Q') {
               return true;
           }
           if (charBoard[i*8+fileL] != ' ') {
               clearL = false;
           }
       }
    }
    clearR = true;
    clearL = true;
    fileR = square % 8;
    fileL = square % 8;
    // bishop moves up (rank number goes down)
    for (int i = rank-1 ; i >= 0 ; i-- ) {
       fileR++;
       if (fileR < 8 && clearR) {
           if (charBoard[i*8 + fileR] == 'B' ||charBoard[i*8 + fileR] == 'Q') {
               return true;
           }
           if (charBoard[i*8 + fileR] != ' ') {
               clearR = false;
           }
       }
       fileL--;
       if (fileL >= 0 && clearL) {
           if (charBoard[i*8 + fileL] == 'B' ||charBoard[i*8 + fileL] == 'Q') {
               return true;
           }
           if (charBoard[i*8 + fileL] != ' ') {
               clearR = false;
           }
       }

    }
    // pawn and king attacking squre check
    file = square % 8;
    rank = square / 8;

    // check the King moves one by one clockwise and two pawn attacking squares
    rank--; // move up
    if (rank >= 0 && charBoard[rank*8+file] == 'K') {
        return true;
    }
    file++;
    if (rank >= 0 && file <8 && ( charBoard[rank*8+file] == 'K' || charBoard[rank*8+file] == 'P')) {
        return true;
    }
    rank++; // move right
    if (file <8 && charBoard[rank*8+file] == 'K') {
        return true;
    }
    rank++;  
    if (rank < 8 && file <8 && charBoard[rank*8+file] == 'K') {
        return true;
    }
    file--; // move down
    if (rank < 8 && charBoard[rank*8+file] == 'K') {
        return true;
    }
    file--;
    if (rank < 8 && file >= 0 && charBoard[rank*8+file] == 'K') {
        return true;
    }
    rank--; // move left
    if ( file >= 0 && charBoard[rank*8+file] == 'K') {
        return true;
    }
    rank--;
    if (rank >= 0 && file >= 0 && ( charBoard[rank*8+file] == 'K'||charBoard[rank*8+file] == 'P')) {
        return true;
    }

    return false;

}
bool Bitboards::isWhiteKingInCheck() {
    
    int square;
    for (auto p : whitePiecesPI ) {
        if (p.getPiece() == 'K' ) {
            square = p.getSquare();
            break;
        }

    }
    int file = square % 8;
    int rank = square / 8;
    // lets check rook like moves and if there is black rook or queen there 
    for (int i = file+1 ; i < 8 ; i++ ) {
       // std::cout << "looking square:" << (rank*8+i) << " there is: " << charBoard[rank*8+i]<< "\n";
        if (charBoard[rank*8+i] != ' ') {
            if (charBoard[rank*8+i] == 'r' ||charBoard[rank*8+i] == 'q') {
                return true;
            }
            else {
                break;
            }
        }
    }
    // look to the left
    for (int i = file - 1 ; i >= 0 ; i-- ) {
       // std::cout << "looking square:" << (rank*8+i) << " there is: " << charBoard[rank*8+i]<< "\n";
        if (charBoard[rank*8+i] != ' ') {
            if (charBoard[rank*8+i] == 'r' ||charBoard[rank*8+i] == 'q') {
                return true;
            }
            else {
                break;
            }
        }
    }

    // look down
    for (int i = rank + 1 ; i < 8 ; i++ ) {
        if (charBoard[i*8+file] != ' ') {
            if (charBoard[i*8+file] == 'r' ||charBoard[i*8+file] == 'q') {
                return true;
            }
            else {
                break;
            }
        
        }
    }
    // look up
    for (int i = rank - 1 ; i >= 0 ; i-- ) {
      //  std::cout << "looking square:" << (i*8+file) << " there is: " << charBoard[i*8+file]<< "\n";
        if (charBoard[i*8+file] != ' ') {
            if (charBoard[i*8+file] == 'r' ||charBoard[i*8+file] == 'q') {
                return true;
            }
            else {
                break;
            }
        
        }
    }
    rank = rank - 2;
    file++;
    if (rank >= 0 && file < 8 && charBoard[rank*8+file] == 'n') {
        return true; // whiteKnightMoves[rank*8+file] = 1;
    }
    rank++; file++;
    if (rank >= 0 && file < 8 && charBoard[rank*8+file] == 'n') {
        return true; // whiteKnightMoves[rank*8+file] = 1;
    }
    rank++; rank++;
    if (rank < 8 && file < 8 && charBoard[rank*8+file] == 'n') {
        return true; // whiteKnightMoves[rank*8+file] = 1;
    }
    rank++;file--;
    if (rank < 8 && file < 8 && charBoard[rank*8+file] == 'n') {
        return true; // whiteKnightMoves[rank*8+file] = 1;
    }
    // Knight moves to left clockwise still
    file--;file--;
    if (rank < 8 && file >= 0 && charBoard[rank*8+file] == 'n') {
        return true; // whiteKnightMoves[rank*8+file] = 1;
    }
    rank--;file--;
    if (rank < 8 && file >= 0 && charBoard[rank*8+file] == 'n') {
        return true; // whiteKnightMoves[rank*8+file] = 1;
    }
    rank--;rank--;
    if (rank >= 0 && file >= 0 && charBoard[rank*8+file] == 'n') {
        return true; // whiteKnightMoves[rank*8+file] = 1;
    }
    rank--;file++;
    if (rank >= 0 && file >= 0 && charBoard[rank*8+file] == 'n') {
        return true; // whiteKnightMoves[rank*8+file] = 1;
    }
    file = square % 8;
    int fileR = square % 8;
    int fileL = square % 8;
    rank = square / 8;
    bool clearR = true;
    bool clearL = true;
    // bishop moves down (rankn number goes up) one rank at a time 
    for (int i = rank+1; i < 8 ; i++ ) {
       fileR++;
       // At every rank look one file to right
       if (fileR < 8 && clearR) {
           // if there is own/white piece can't move there
           if (charBoard[i*8+fileR] == 'b' ||charBoard[i*8+fileR] == 'q') {
               return true;
           }
           if (charBoard[i*8+fileR] != ' ') {
               clearR = false;
           }
       }
       fileL--;
       // bishop moves down and left
       if (fileL >= 0 && clearL) {
           if (charBoard[i*8+fileL] == 'b' ||charBoard[i*8+fileL] == 'q') {
               return true;
           }
           if (charBoard[i*8+fileL] != ' ') {
               clearL = false;
           }
       }
    }
    clearR = true;
    clearL = true;
    fileR = square % 8;
    fileL = square % 8;
    // bishop moves up (rank number goes down)
    for (int i = rank-1 ; i >= 0 ; i-- ) {
       fileR++;
       if (fileR < 8 && clearR) {
           if (charBoard[i*8 + fileR] == 'b' ||charBoard[i*8 + fileR] == 'q') {
               return true;
           }
           if (charBoard[i*8 + fileR] != ' ') {
               clearR = false;
           }
       }
       fileL--;
       if (fileL >= 0 && clearL) {
           if (charBoard[i*8 + fileL] == 'b' ||charBoard[i*8 + fileL] == 'q') {
               return true;
           }
           if (charBoard[i*8 + fileL] != ' ') {
               clearR = false;
           }
       }

    }
    // pawn and king attacking squre check
    file = square % 8;
    rank = square / 8;

    // check the King moves one by one clockwise and two pawn attacking squares
    rank--; // move up
    if (rank >= 0 && charBoard[rank*8+file] == 'k') {
        return true;
    }
    file++;
    if (rank >= 0 && file <8 && ( charBoard[rank*8+file] == 'k' || charBoard[rank*8+file] == 'p')) {
        return true;
    }
    rank++; // move right
    if (file <8 && charBoard[rank*8+file] == 'k') {
        return true;
    }
    rank++;  
    if (rank < 8 && file <8 && charBoard[rank*8+file] == 'k' ){
        return true;
    }
    file--; // move down
    if (rank < 8 && charBoard[rank*8+file] == 'k') {
        return true;
    }
    file--;
    if (rank < 8 && file >= 0 && charBoard[rank*8+file] == 'k') {
        return true;
    }
    rank--; // move left
    if ( file >= 0 && charBoard[rank*8+file] == 'k') {
        return true;
    }
    rank--;
    if (rank >= 0 && file >= 0 && ( charBoard[rank*8+file] == 'k'||charBoard[rank*8+file] == 'p')) {
        return true;
    }
    return false;
}




std::bitset<64> Bitboards::getAttackingMoves(int square, char piece) {

    switch(piece) {
        case 'R':
            return getWhiteRookMoves(square);
        case 'N':
            return getWhiteKnightMoves(square);
        case 'B':
            return getWhiteBishopMoves(square);
        case 'K':
            return getWhiteKingMoves(square);
        case 'Q':
            return getWhiteQueenMoves(square);
        case 'P':
            return getWhitePawnAttackingMoves(square) |= getWhitePawnMoves(square);
        case 'r':
            return getBlackRookMoves(square);
        case 'n':
            return getBlackKnightMoves(square);
        case 'b':
            return getBlackBishopMoves(square);
        case 'k':
            return getBlackKingMoves(square);
        case 'q':
            return getBlackQueenMoves(square);
        case 'p':
            return getBlackPawnAttackingMoves(square) |= getBlackPawnMoves(square);
        default:

            std::bitset<64> empty;
            //std::cout << "ups";
            return empty;
    }
}
// This method should guarantee that moves are legal
std::bitset<64> Bitboards::getLegalMoves(int square) {
    for (int i = 0 ; i < whitePiecesPI.size() ; i++) {
        if (whitePiecesPI.at(i).getSquare() == square) {
            return whitePiecesPI.at(i).getLegalMoves();
        }
    }
    for (int i = 0 ; i < blackPiecesPI.size() ; i++) {
        if (blackPiecesPI.at(i).getSquare() == square) {
            return blackPiecesPI.at(i).getLegalMoves();
        }
    }

    std::bitset<64> empty;
    return empty;

}
// This is used inside bitboards, probably should be private, does not guarantee that 
// every move ginven this method is really legal
std::bitset<64> Bitboards::getLegalMoves(int square, char piece) {
/*
    for (int i = 0 ; i < whitePiecesPI.size() ; i++) {
        if (whitePiecesPI.at(i).getPiece() == piece) {
            return whitePiecesPI.at(i).getLegalMoves();
        }
    }
   */ 
    switch(piece) {
        case 'R':
            return getWhiteRookMoves(square);
        case 'N':
            return getWhiteKnightMoves(square);
        case 'B':
            return getWhiteBishopMoves(square);
        case 'K':
            return getWhiteKingMoves(square);
        case 'Q':
            return getWhiteQueenMoves(square);
        case 'P':
            return getWhitePawnMoves(square);
        case 'r':
            return getBlackRookMoves(square);
        case 'n':
            return getBlackKnightMoves(square);
        case 'b':
            return getBlackBishopMoves(square);
        case 'k':
            return getBlackKingMoves(square);
        case 'q':
            return getBlackQueenMoves(square);
        case 'p':
            return getBlackPawnMoves(square);
        default:

            std::bitset<64> empty;
            //std::cout << "ups";
            return empty;
    }
    
}
void Bitboards::printBitboard(std::bitset<64> pb) {

    for (int i = 0; i< pb.size() ; i++) {
        if (pb[i] == 1) {
        std::cout << "\033[1;32m" << pb[i] << "\033[0m";
        } else {
            std::cout <<pb[i];
        }
        if ( (i+1) % 8 == 0 ) {
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

std::bitset<64> Bitboards::getBlackRookMoves(int square) {


    std::bitset<64> blackRookMoves;
    int file = square % 8;
    int rank = square / 8;
    // look to the right
    for (int i = file+1 ; i < 8 ; i++ ) {
        if (blackPieces[rank*8+i] == 0) {
            blackRookMoves[rank*8+i] = 1;
            if ( whitePieces[rank*8+i] == 1 ) {break; }
        }
        else {break; }

    }
    // look to the left
    for (int i = file - 1 ; i >= 0 ; i-- ) {

        if (blackPieces[rank*8+i] == 0) {
            blackRookMoves[rank*8+i] = 1;
            if ( whitePieces[rank*8+i] == 1 ) {break; }
        }
        else {break; }
    }

    // look down
    for (int i = rank + 1 ; i < 8 ; i++ ) {
        
        if (blackPieces[i*8+file] == 0) {
            blackRookMoves[i*8+file] = 1;
            if ( whitePieces[i*8+file] == 1 ) {break; }
        }
        else {break; }
        
    }
    // look up
    for (int i = rank - 1 ; i >= 0 ; i-- ) {
        if (blackPieces[i*8+file] == 0) {
            blackRookMoves[i*8+file] = 1;
            if ( whitePieces[i*8+file] == 1 ) {break; }
        }
        else {break; }
        
    }
    return blackRookMoves;
}


std::bitset<64> Bitboards::getWhiteRookMoves(int square) {

    std::bitset<64> whiteRookMoves;
    int file = square % 8;
    int rank = square / 8;
    // look to the right
    for (int i = file+1 ; i < 8 ; i++ ) {
        if (whitePieces[rank*8+i] == 0) {
            whiteRookMoves[rank*8+i] = 1;
            if ( blackPieces[rank*8+i] == 1 ) {break; }
        }
        else {break; }

    }
    // look to the left
    for (int i = file - 1 ; i >= 0 ; i-- ) {

        if (whitePieces[rank*8+i] == 0) {
            whiteRookMoves[rank*8+i] = 1;
            if ( blackPieces[rank*8+i] == 1 ) {break; }
        }
        else {break; }
    }

    // look down
    for (int i = rank + 1 ; i < 8 ; i++ ) {
        
        if (whitePieces[i*8+file] == 0) {
            whiteRookMoves[i*8+file] = 1;
            if ( blackPieces[i*8+file] == 1 ) {break; }
        }
        else {break; }
        
    }
    // look up
    for (int i = rank - 1 ; i >= 0 ; i-- ) {
        if (whitePieces[i*8+file] == 0) {
            whiteRookMoves[i*8+file] = 1;
            if ( blackPieces[i*8+file] == 1 ) {break; }
        }
        else {break; }
        
    }
    return whiteRookMoves;
}

std::bitset<64> Bitboards::getBlackKnightMoves(int square) {

    std::bitset<64> blackKnightMoves;
    int file = square % 8;
    int rank = square / 8;

    //std::cout << "file: " << file << " rank: " << rank << "\n";
    // check the knight moves clockwise
    rank = rank - 2;
    file++;
    if (rank >= 0 && file < 8 && blackPieces[rank*8+file] == 0) {
        blackKnightMoves[rank*8+file] = 1;
    }
    rank++; file++;
    if (rank >= 0 && file < 8 && blackPieces[rank*8+file] == 0) {
        blackKnightMoves[rank*8+file] = 1;
    }
    rank++; rank++;
    if (rank < 8 && file < 8 && blackPieces[rank*8+file] == 0) {
        blackKnightMoves[rank*8+file] = 1;
    }
    rank++;file--;
    if (rank < 8 && file < 8 && blackPieces[rank*8+file] == 0) {
        blackKnightMoves[rank*8+file] = 1;
    }
    // Knight moves to left clockwise still
    file--;file--;
    if (rank < 8 && file >= 0 && blackPieces[rank*8+file] == 0) {
        blackKnightMoves[rank*8+file] = 1;
    }
    rank--;file--;
    if (rank < 8 && file >= 0 && blackPieces[rank*8+file] == 0) {
        blackKnightMoves[rank*8+file] = 1;
    }
    rank--;rank--;
    if (rank >= 0 && file >= 0 && blackPieces[rank*8+file] == 0) {
        blackKnightMoves[rank*8+file] = 1;
    }
    rank--;file++;
    if (rank >= 0 && file >= 0 && blackPieces[rank*8+file] == 0) {
        blackKnightMoves[rank*8+file] = 1;
    }
    
    return blackKnightMoves;

}

std::bitset<64> Bitboards::getWhiteKnightMoves(int square) {

    std::bitset<64> whiteKnightMoves;
    int file = square % 8;
    int rank = square / 8;

    //std::cout << "file: " << file << " rank: " << rank << "\n";
    // check the knight moves clockwise
    rank = rank - 2;
    file++;
    if (rank >= 0 && file < 8 && whitePieces[rank*8+file] == 0) {
        whiteKnightMoves[rank*8+file] = 1;
    }
    rank++; file++;
    if (rank >= 0 && file < 8 && whitePieces[rank*8+file] == 0) {
        whiteKnightMoves[rank*8+file] = 1;
    }
    rank++; rank++;
    if (rank < 8 && file < 8 && whitePieces[rank*8+file] == 0) {
        whiteKnightMoves[rank*8+file] = 1;
    }
    rank++;file--;
    if (rank < 8 && file < 8 && whitePieces[rank*8+file] == 0) {
        whiteKnightMoves[rank*8+file] = 1;
    }
    // Knight moves to left clockwise still
    file--;file--;
    if (rank < 8 && file >= 0 && whitePieces[rank*8+file] == 0) {
        whiteKnightMoves[rank*8+file] = 1;
    }
    rank--;file--;
    if (rank < 8 && file >= 0 && whitePieces[rank*8+file] == 0) {
        whiteKnightMoves[rank*8+file] = 1;
    }
    rank--;rank--;
    if (rank >= 0 && file >= 0 && whitePieces[rank*8+file] == 0) {
        whiteKnightMoves[rank*8+file] = 1;
    }
    rank--;file++;
    if (rank >= 0 && file >= 0 && whitePieces[rank*8+file] == 0) {
        whiteKnightMoves[rank*8+file] = 1;
    }
    
    return whiteKnightMoves;

}


std::bitset<64> Bitboards::getBlackBishopMoves(int square) {

    std::bitset<64> blackBishopMoves;
    int file = square % 8;
    int fileR = square % 8;
    int fileL = square % 8;
    int rank = square / 8;
    bool clearR = true;
    bool clearL = true;
    // bishop moves down (rankn number goes up) one rank at a time 
    for (int i = rank+1; i < 8 ; i++ ) {
       fileR++;
       // At every rank look one file to right
       if (fileR < 8 && clearR) {
           // if there is own/white piece can't move there
           if (blackPieces[i*8+fileR] == 0) {
               blackBishopMoves[i*8+fileR] = 1;
               // if there is other color piece, can move there but not past that piece
               if (whitePieces[i*8+fileR] == 1) {
                   clearR = false;
               }
           }
           else {
               clearR = false;
           }
       }
       fileL--;
       // bishop moves down and left
       if (fileL >= 0 && clearL) {
           if (blackPieces[i*8+fileL] == 0) {
               blackBishopMoves[i*8+fileL] = 1;
               if(whitePieces[i*8+fileL] == 1) {
                   clearL = false;
               }
           }
           else {
               clearL = false;
           }
       }
    }
    clearR = true;
    clearL = true;
    fileR = square % 8;
    fileL = square % 8;
    // bishop moves up (rank number goes down)
    for (int i = rank-1 ; i >= 0 ; i-- ) {
       fileR++;
       if (fileR < 8 && clearR) {
           if (blackPieces[i*8 + fileR] == 0) {
               blackBishopMoves[i*8+fileR] = 1;
               if (whitePieces[i*8 + fileR] == 1) {
                   clearR = false;
               } 
           }
           else {
               clearR = false;
           }
       }
       fileL--;
       if (fileL >= 0 && clearL) {
           if (blackPieces[i*8 + fileL] == 0 ) {
               blackBishopMoves[i*8+fileL] = 1;
               if (whitePieces[i*8 + fileL] == 1) {
                   clearL = false;
                  }
           }
           else {
               clearL = false;
           }
       }

    }
    return blackBishopMoves;

}

std::bitset<64> Bitboards::getWhiteBishopMoves(int square) {

    std::bitset<64> whiteBishopMoves;
    int file = square % 8;
    int fileR = square % 8;
    int fileL = square % 8;
    int rank = square / 8;
    bool clearR = true;
    bool clearL = true;
    // bishop moves down (rankn number goes up) one rank at a time 
    for (int i = rank+1; i < 8 ; i++ ) {
       fileR++;
       // At every rank look one file to right
       if (fileR < 8 && clearR) {
           // if there is own/white piece can't move there
           if (whitePieces[i*8+fileR] == 0) {
               whiteBishopMoves[i*8+fileR] = 1;
               // if there is other color piece, can move there but not past that piece
               if (blackPieces[i*8+fileR] == 1) {
                   clearR = false;
               }
           }
           else {
               clearR = false;
           }
       }
       fileL--;
       // bishop moves down and left
       if (fileL >= 0 && clearL) {
           if (whitePieces[i*8+fileL] == 0) {
               whiteBishopMoves[i*8+fileL] = 1;
               if(blackPieces[i*8+fileL] == 1) {
                   clearL = false;
               }
           }
           else {
               clearL = false;
           }
       }
    }
    clearR = true;
    clearL = true;
    fileR = square % 8;
    fileL = square % 8;
    // bishop moves up (rank number goes down)
    for (int i = rank-1 ; i >= 0 ; i-- ) {
       fileR++;
       if (fileR < 8 && clearR) {
           if (whitePieces[i*8 + fileR] == 0) {
               whiteBishopMoves[i*8+fileR] = 1;
               if (blackPieces[i*8 + fileR] == 1) {
                   clearR = false;
               } 
           }
           else {
               clearR = false;
           }
       }
       fileL--;
       if (fileL >= 0 && clearL) {
           if (whitePieces[i*8 + fileL] == 0 ) {
               whiteBishopMoves[i*8+fileL] = 1;
               if (blackPieces[i*8 + fileL] == 1) {
                   clearL = false;
                  }
           }
           else {
               clearL = false;
           }
       }

    }
    return whiteBishopMoves;

}

// Remember to remove squres that white is attacking
std::bitset<64> Bitboards::getBlackKingMoves(int square) {

    std::bitset<64> blackKingMoves;
    int file = square % 8;
    int rank = square / 8;

    // check the King moves one by one clockwise
    rank--; // move up
    if (rank >= 0 && blackPieces[rank*8+file] == 0) {
        blackKingMoves[rank*8+file] = 1;
    }
    file++;
    if (rank >= 0 && file <8 && blackPieces[rank*8+file] == 0) {
        blackKingMoves[rank*8+file] = 1;
    }
    rank++; // move right
    if (file <8 && blackPieces[rank*8+file] == 0) {
        blackKingMoves[rank*8+file] = 1;
    }
    rank++;  
    if (rank < 8 && file <8 && blackPieces[rank*8+file] == 0) {
        blackKingMoves[rank*8+file] = 1;
    }
    file--; // move down
    if (rank < 8 && blackPieces[rank*8+file] == 0) {
        blackKingMoves[rank*8+file] = 1;
    }
    file--;
    if (rank < 8 && file >= 0 && blackPieces[rank*8+file] == 0) {
        blackKingMoves[rank*8+file] = 1;
    }
    rank--; // move left
    if ( file >= 0 && blackPieces[rank*8+file] == 0) {
        blackKingMoves[rank*8+file] = 1;
    }
    rank--;
    if (rank >= 0 && file >= 0 && blackPieces[rank*8+file] == 0) {
        blackKingMoves[rank*8+file] = 1;
    }
    return blackKingMoves;
}
// Remember to remove squares that black is attacking
std::bitset<64> Bitboards::getWhiteKingMoves(int square) {

    std::bitset<64> whiteKingMoves;
    int file = square % 8;
    int rank = square / 8;

    // check the King moves one by one clockwise
    rank--; // move up
    if (rank >= 0 && whitePieces[rank*8+file] == 0) {
        whiteKingMoves[rank*8+file] = 1;
    }
    file++;
    if (rank >= 0 && file <8 && whitePieces[rank*8+file] == 0) {
        whiteKingMoves[rank*8+file] = 1;
    }
    rank++; // move right
    if (file <8 && whitePieces[rank*8+file] == 0) {
        whiteKingMoves[rank*8+file] = 1;
    }
    rank++;  
    if (rank < 8 && file <8 && whitePieces[rank*8+file] == 0) {
        whiteKingMoves[rank*8+file] = 1;
    }
    file--; // move down
    if (rank < 8 && whitePieces[rank*8+file] == 0) {
        whiteKingMoves[rank*8+file] = 1;
    }
    file--;
    if (rank < 8 && file >= 0 && whitePieces[rank*8+file] == 0) {
        whiteKingMoves[rank*8+file] = 1;
    }
    rank--; // move left
    if ( file >= 0 && whitePieces[rank*8+file] == 0) {
        whiteKingMoves[rank*8+file] = 1;
    }
    rank--;
    if (rank >= 0 && file >= 0 && whitePieces[rank*8+file] == 0) {
        whiteKingMoves[rank*8+file] = 1;
    }
    return whiteKingMoves;
}

std::bitset<64> Bitboards::getBlackQueenMoves(int square) {

    std::bitset<64> blackQueenMoves;
    int file = square % 8;
    int rank = square / 8;
    // look to the right
    for (int i = file+1 ; i < 8 ; i++ ) {
        if (blackPieces[rank*8+i] == 0) {
            blackQueenMoves[rank*8+i] = 1;
            if ( whitePieces[rank*8+i] == 1 ) {break; }
        }
        else {break; }

    }
    // look to the left
    for (int i = file - 1 ; i >= 0 ; i-- ) {

        if (blackPieces[rank*8+i] == 0) {
            blackQueenMoves[rank*8+i] = 1;
            if ( whitePieces[rank*8+i] == 1 ) {break; }
        }
        else {break; }
    }

    // look down
    for (int i = rank + 1 ; i < 8 ; i++ ) {
        
        if (blackPieces[i*8+file] == 0) {
            blackQueenMoves[i*8+file] = 1;
            if ( whitePieces[i*8+file] == 1 ) {break; }
        }
        else {break; }
        
    }
    // look up
    for (int i = rank - 1 ; i >= 0 ; i-- ) {
        if (blackPieces[i*8+file] == 0) {
            blackQueenMoves[i*8+file] = 1;
            if ( whitePieces[i*8+file] == 1 ) {break; }
        }
        else {break; }
        
    }

    int fileR = square % 8;
    int fileL = square % 8;
    bool clearR = true;
    bool clearL = true;
    // Add Queen moves that are like Bishopmoves
    for (int i = rank+1; i < 8 ; i++ ) {
       fileR++;
       if (fileR < 8 && clearR) {
           if (blackPieces[i*8+fileR] == 0) {
               blackQueenMoves[i*8+fileR] = 1;
               if (whitePieces[i*8+fileR] == 1) {
                   clearR = false;
               }
           }
           else {
               clearR = false;
           }
       }
       fileL--;
       if (fileL >= 0 && clearL) {
           if (blackPieces[i*8+fileL] == 0) {
               blackQueenMoves[i*8+fileL] = 1;
               if(whitePieces[i*8+fileL] == 1) {
                   clearL = false;
               }
           }
           else {
               clearL = false;
           }
       }
    }
    clearR = true;
    clearL = true;
    fileR = square % 8;
    fileL = square % 8;
    for (int i = rank-1 ; i >= 0 ; i-- ) {
       fileR++;
       if (fileR < 8 && clearR) {
           if (blackPieces[i*8 + fileR] == 0) {
               blackQueenMoves[i*8+fileR] = 1;
               if (whitePieces[i*8 + fileR] == 1) {
                   clearR = false;
               } 
           }
           else {
               clearR = false;
           }
       }
       fileL--;
       if (fileL >= 0 && clearL) {
           if (blackPieces[i*8 + fileL] == 0 ) {
               blackQueenMoves[i*8+fileL] = 1;
               if (whitePieces[i*8 + fileL] == 1) {
                   clearL = false;
                  }
           }
           else {
               clearL = false;
           }
       }

    }
    return blackQueenMoves;
}

std::bitset<64> Bitboards::getWhiteQueenMoves(int square) {

    std::bitset<64> whiteQueenMoves;
    int file = square % 8;
    int rank = square / 8;
    // look to the right
    for (int i = file+1 ; i < 8 ; i++ ) {
        if (whitePieces[rank*8+i] == 0) {
            whiteQueenMoves[rank*8+i] = 1;
            if ( blackPieces[rank*8+i] == 1 ) {break; }
        }
        else {break; }

    }
    // look to the left
    for (int i = file - 1 ; i >= 0 ; i-- ) {

        if (whitePieces[rank*8+i] == 0) {
            whiteQueenMoves[rank*8+i] = 1;
            if ( blackPieces[rank*8+i] == 1 ) {break; }
        }
        else {break; }
    }

    // look down
    for (int i = rank + 1 ; i < 8 ; i++ ) {
        
        if (whitePieces[i*8+file] == 0) {
            whiteQueenMoves[i*8+file] = 1;
            if ( blackPieces[i*8+file] == 1 ) {break; }
        }
        else {break; }
        
    }
    // look up
    for (int i = rank - 1 ; i >= 0 ; i-- ) {
        if (whitePieces[i*8+file] == 0) {
            whiteQueenMoves[i*8+file] = 1;
            if ( blackPieces[i*8+file] == 1 ) {break; }
        }
        else {break; }
        
    }

    int fileR = square % 8;
    int fileL = square % 8;
    bool clearR = true;
    bool clearL = true;
    // Add Queen moves that are like Bishopmoves
    for (int i = rank+1; i < 8 ; i++ ) {
       fileR++;
       if (fileR < 8 && clearR) {
           if (whitePieces[i*8+fileR] == 0) {
               whiteQueenMoves[i*8+fileR] = 1;
               if (blackPieces[i*8+fileR] == 1) {
                   clearR = false;
               }
           }
           else {
               clearR = false;
           }
       }
       fileL--;
       if (fileL >= 0 && clearL) {
           if (whitePieces[i*8+fileL] == 0) {
               whiteQueenMoves[i*8+fileL] = 1;
               if(blackPieces[i*8+fileL] == 1) {
                   clearL = false;
               }
           }
           else {
               clearL = false;
           }
       }
    }
    clearR = true;
    clearL = true;
    fileR = square % 8;
    fileL = square % 8;
    for (int i = rank-1 ; i >= 0 ; i-- ) {
       fileR++;
       if (fileR < 8 && clearR) {
           if (whitePieces[i*8 + fileR] == 0) {
               whiteQueenMoves[i*8+fileR] = 1;
               if (blackPieces[i*8 + fileR] == 1) {
                   clearR = false;
               } 
           }
           else {
               clearR = false;
           }
       }
       fileL--;
       if (fileL >= 0 && clearL) {
           if (whitePieces[i*8 + fileL] == 0 ) {
               whiteQueenMoves[i*8+fileL] = 1;
               if (blackPieces[i*8 + fileL] == 1) {
                   clearL = false;
                  }
           }
           else {
               clearL = false;
           }
       }

    }
    return whiteQueenMoves;
}



std::bitset<64> Bitboards::getBlackPawnMoves(int square) {

    std::bitset<64> blackPawnMoves;
    int file = square % 8;
    int rank = square / 8;
    if (rank == 7) {
        std::cout << "impossible pawn square: " << square << "\n";
    }
    if ( rank == 1 ) {
        rank++;
        if ( blackPieces[rank*8+file] == 0 && whitePieces[rank*8+file] == 0) {
            blackPawnMoves[rank*8+file] = 1;
            rank++;
            if ( blackPieces[rank*8+file] == 0 && whitePieces[rank*8+file] == 0) {
                blackPawnMoves[rank*8+file] = 1;
            }
        }

    }
    else {
        rank++;
        if ( blackPieces[rank*8+file] == 0 && whitePieces[rank*8+file] == 0) {
            blackPawnMoves[rank*8+file] = 1;
        }
        if ( rank == 7 ) {
            std::cout << "create a new piece" << "\n";
        }
    }
    rank = square / 8 +1;
    file++;     
    if ( file >= 0 && rank >= 0 && whitePieces[rank*8+file] == 1) {
        blackPawnMoves[rank*8+file] = 1;
    }
    file--;file--;
    if ( file < 8 && rank >= 0 && whitePieces[rank*8+file] == 1) {
        blackPawnMoves[rank*8+file] = 1;
    }

    return blackPawnMoves;
}
std::bitset<64> Bitboards::getBlackPawnAttackingMoves(int square) {

    std::bitset<64> blackPawnAttackingMoves;
    int file = square % 8;
    int rank = square / 8 +1;
    file--;     
    if ( file >= 0 && rank >= 0 && whitePieces[rank*8+file] == 1) {
        blackPawnAttackingMoves[rank*8+file] = 1;
    }
    file++;file++;
    if ( file < 8 && rank >= 0 && whitePieces[rank*8+file] == 1) {
        blackPawnAttackingMoves[rank*8+file] = 1;
    }

    return blackPawnAttackingMoves;
}
std::bitset<64> Bitboards::getWhitePawnAttackingMoves(int square) {

    std::bitset<64> whitePawnAttackingMoves;
    int file = square % 8;
    int rank = square / 8 -1;
    file--;     
    if ( file >= 0 && rank >= 0 && blackPieces[rank*8+file] == 1) {
        whitePawnAttackingMoves[rank*8+file] = 1;
    }
    file++;file++;
    if ( file < 8 && rank >= 0 && blackPieces[rank*8+file] == 1) {
        whitePawnAttackingMoves[rank*8+file] = 1;
    }

    return whitePawnAttackingMoves;
}
std::bitset<64> Bitboards::getWhitePawnMoves(int square) {

    std::bitset<64> whitePawnMoves;
    int file = square % 8;
    int rank = square / 8;
    if (rank == 0) {
        std::cout << "impossible pawn square: " << square << "\n";
    }
    if ( rank == 6 ) {
        rank--;
        if ( whitePieces[rank*8+file] == 0 && blackPieces[rank*8+file] == 0) {
            whitePawnMoves[rank*8+file] = 1;
            rank--;
            if ( whitePieces[rank*8+file] == 0 && blackPieces[rank*8+file] == 0) {
                whitePawnMoves[rank*8+file] = 1;
            }
        }

    }
    else {
        rank--;
        if ( whitePieces[rank*8+file] == 0 && blackPieces[rank*8+file] == 0) {
            whitePawnMoves[rank*8+file] = 1;
        }
        if ( rank == 0 ) {
            std::cout << "create a new piece" << "\n";
        }
    }
    rank = square / 8 -1;
    file--;     
    if ( file >= 0 && rank >= 0 && blackPieces[rank*8+file] == 1) {
        whitePawnMoves[rank*8+file] = 1;
    }
    file++;file++;
    if ( file < 8 && rank >= 0 && blackPieces[rank*8+file] == 1) {
        whitePawnMoves[rank*8+file] = 1;
    }

    return whitePawnMoves;
}
