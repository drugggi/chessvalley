#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>

class Chessboard {
    private:
        std::array<char,64> SQ = { 'r','n','b','q','k','b','n','r',
                'p','p','p','p','p','p','p','p',
                ' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',

                ' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',
                'P','P','P','P','P','P','P','P',
                'R','N','B','Q','K','B','N','R' };
    char squares[64] = { 'r','n','b','q','k','b','n','r',
                'p','p','p','p','p','p','p','p',
                ' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',

                ' ',' ',' ',' ',' ',' ',' ',' ',
                ' ',' ',' ',' ',' ',' ',' ',' ',
                'P','P','P','P','P','P','P','P',
                'R','N','B','Q','K','B','N','R' };
        void movePiece(char piece, int moveTo);
        void updateBoard(int pieceFrom, int pieceTo);
    public:
        Chessboard();
        const void printChessboard();
        bool moveCommand(std::string command);
        

};

#endif
