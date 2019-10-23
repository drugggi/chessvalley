#ifndef PIECEINFO_H
#define PIECEINFO_H

#include <bitset>
#include <iostream>
#include <vector>

class PieceInfo {
    private:
        char piece;
        int square;
        std::bitset<64> legalMoves;
        int value;

    public:
        PieceInfo(char p,int s);
        ~PieceInfo();
        void setLegalMoves(std::bitset<64> lm);
        void printPieceInfo();
        void printLegalMoveCoordinates();
        int getSquare();
        void setSquare(int newSquare);
        char getPiece();
        int getValue();
        std::bitset<64> getLegalMoves();
        std::vector<int> getLegalMoveSquares();


};
#endif
