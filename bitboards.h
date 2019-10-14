 #ifndef BITBOARDS_H
#define BITBOARDS_H

#include <array>
#include <bitset>

class Bitboards {
    private:
        std::bitset<64> occupiedSquares;
        std::bitset<64> whitePieces;
       std::bitset<64> blackPieces;

        std::bitset<64> whiteRook;
        std::bitset<64> whiteKnight;
        std::bitset<64> whiteBishop;
        std::bitset<64> whiteKing;
        std::bitset<64> whiteQueen;
        std::bitset<64> whitePawn;
    public:
        Bitboards(std::array<char,64> SQ);
        void printBitboard(std::bitset<64> pb);
        std::bitset<64> getLegalMoves(int square, char piece);

        std::bitset<64> getWhiteRookMoves(int square);
        std::bitset<64> getWhiteKnightMoves(int square);
        std::bitset<64> getWhiteBishopMoves(int square);
        std::bitset<64> getWhiteKingMoves(int square);
        std::bitset<64> getWhiteQueenMoves(int square);
        std::bitset<64> getWhitePawnMoves(int square);

        std::bitset<64> getBlackRookMoves(int square);
        std::bitset<64> getBlackKnightMoves(int square);
        std::bitset<64> getBlackBishopMoves(int square);
        std::bitset<64> getBlackKingMoves(int square);
        std::bitset<64> getBlackQueenMoves(int square);
        std::bitset<64> getBlackPawnMoves(int square);
};



#endif
