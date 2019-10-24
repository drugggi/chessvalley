#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>
#include <bitset>
#include <vector>
#include "bitboards.h"
#include "pieceinfo.h"

class Chessboard {
    private:
        bool whitesTurn = true;
        int enpassant = 0;
        bool castledKingside = false;
        bool castledQueenside = false;

        int highlightSquare = -1;
        Bitboards* bbs;
        std::array<char,64> SQ2 = { ' ',' ',' ',' ','k','b',' ','r',
                ' ',' ',' ','p',' ','p',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',
                'R',' ',' ',' ',' ',' ',' ',' ',

                'K',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ','P',' ',' ',' ',
                ' ','N','B','Q',' ','B',' ','R' };
        std::array<char,64> SQ = { 'r','n','b','q','k','b','n','r',
                'p','p','p','p','p','p','p','p',
                ' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',

                ' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',
                'P','P','P','P','P','P','P','P',
                'R','N','B','Q','K','B','N','R' };

        void movePiece(char piece, int moveTo);
        void updateBoard(int pieceFrom, int pieceTo);
        void movePiece(int from, int to);
        std::vector<int> moveHistory;
    public:
        Chessboard();
        ~Chessboard();
        int getSquare(std::string coordinate);
        const void printChessboard();
        const void printBoardPieces();
        const void printMoveHistory();
        bool moveCommand(std::string command);
        bool isWhitesTurn();
        // void testBitset();
        int whereIsPiece(char piece); 
        static std::string coordinate(int square);

        void computerMovesRandomly();
        void computerMovesNonRandomly();
};

#endif
