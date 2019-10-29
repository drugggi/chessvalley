#include <iostream>
#include <vector>

#include "chessboard.h"
#include "pieceinfo.h"

PieceInfo::PieceInfo(char p, int s) {
    piece = p;
    square = s;

    if (p == 'p' || p == 'P' ||p == 'k' || p == 'K') {
        value = 1;
    }
    else if (p == 'b' ||p == 'B' || p == 'n' ||p == 'N') {
        value = 3;
    }
    else if (p == 'r' ||p == 'R') {
        value = 4;
    }
    else if (p == 'q' ||p == 'Q') {
        value = 6;
    }
}

PieceInfo::~PieceInfo() {

}
float PieceInfo::getValue() {
    return value;
}
char PieceInfo::getPiece() {
    return piece;
}
int PieceInfo::getSquare() {
    return square;
}
void PieceInfo::setSquare(int newSquare) {
    square = newSquare;
}

void PieceInfo::setLegalMoves(std::bitset<64> lm) {
    legalMoves = lm;
}

void PieceInfo::setLegalMove(int moveSquare, bool allowed) {
//    std::cout << piece << Chessboard::coordinate(moveSquare) << " reverted\n";
    if (allowed) {
        legalMoves[moveSquare] = 1;
    }
    else {
        legalMoves[moveSquare] = 0;
    }
}
std::bitset<64> PieceInfo::getLegalMoves() {
    return legalMoves;
}

void PieceInfo::printPieceInfo() {

    std::cout << piece << "(" << Chessboard::coordinate(square) << ") -> ";
    printLegalMoveCoordinates();
    std::cout << " | ";
//    std::cout << "\n";
}

std::vector<int> PieceInfo::getLegalMoveSquares() {

    std::vector<int> moveSquares;
    for (int i = 0 ; i < legalMoves.size() ; i++ ) {
        if (legalMoves[i] == 1 ) {
            moveSquares.push_back(i);
        }
    }
    return moveSquares;
}

void PieceInfo::printLegalMoveCoordinates() {
    if (legalMoves.any() == false ) {
        std::cout << " NaN ";
    }
    for (int i = 0 ; i < legalMoves.size() ; i++) {
        if (legalMoves[i] == 1 ) {
            std::cout << Chessboard::coordinate(i) << " ";
        }
    }
}
