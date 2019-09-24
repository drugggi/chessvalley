#include <iostream>
#include <array>
#include <vector>
#include "chessboard.h"

Chessboard::Chessboard() {


}

const void Chessboard::printChessboard() {

    std::cout << "––––– ––––– ––––– ––––– ––––– ––––– ––––– –––––\n";
    for (int i = 0; i < 64 ; i++ ) {
        std::cout << "| "<< squares[i] << " | ";
        if ((i+1) % 8 == 0 ) {
            std::cout << "\n"
                << "––––– ––––– ––––– ––––– ––––– ––––– ––––– –––––\n";
        }

    }


}

bool Chessboard::moveCommand(std::string command) {
    if (command.length() < 2) {
        return false;
    }
    bool check = false;
    if (command.at(command.length() - 1 ) == '+') {
        command = command.substr(0, command.length() -1);
        check = true;
        std::cout << "check! " << "new command: " << command << "\n";
    }
/*
    if (command.length() == 2 ) {
        char file = command.at(0);
        char rank = command.at(1);
        int iFile = (int) file-97;
        int iRank = ( (int) rank-56)*-1;

        std::cout << "char taulukossa: char[" << (iRank*8)+(iFile) << "]\n";
        std::cout << "and piece there is: '" << squares[(iRank*8)+(iFile)] << "'\n";
        std::cout << "move pawn file/rank" << iFile << "/" << iRank <<"\n";
    }
    */
    std::vector<char> commandChars; 
    for (int i = 0 ; i < command.length() ; i++) {
        commandChars.push_back( command.at(i) );
    }
    char file = commandChars.at( commandChars.size() - 2);
    char rank = commandChars.at( commandChars.size() -1);
//    int iFile = (int) file-97;
 //   int iRank = ( (int) rank-56)*-1;
    int moveTo = (( (int) rank-56)*-8) + ( (int) file-97 );
//    std::cout << file << "  " << rank << "  " << "  " << "  " << moveTo << "\n"; 
    if (moveTo < 0 ||moveTo > 63) {return false; }
    
    char pieceToMove;
    if (commandChars.size() == 2 ) {
        pieceToMove = 'P';
        std::cout << "pawn moves \n";
    }
    else if ( commandChars.size() == 3 ) {
        pieceToMove = commandChars.at(0);
        std::cout << pieceToMove << " moves " << file << rank << "\n";
    }
    else if ( commandChars.size() == 4 ) {

        pieceToMove = commandChars.at(0);
        if (commandChars.at(1) == 'x') {
            std::cout << pieceToMove << " takes "<< file << rank << "\n";
        }
        else {
            std::cout << pieceToMove << " from " << commandChars.at(1) << " moves " << file
                << rank << "\n";
        }
    }
    movePiece(pieceToMove, moveTo);
    return true;
}

void Chessboard::movePiece(char piece, int moveTo) {
    std::cout << piece << " moves to square: " << moveTo << "\n";

    if (piece == 'P') {
        if (squares[moveTo+8] == 'P') {
           updateBoard(moveTo+8 , moveTo); 

        } 
        else if (moveTo > 31 % moveTo < 40 && squares[moveTo+16] == 'P' ){
            updateBoard(moveTo+16,moveTo);
        }

     }

    if (piece == 'N') {
        if (squares[moveTo+15] == 'N' ) {
            updateBoard(moveTo+15,moveTo); 
        }
        else if (squares[moveTo+17] == 'N' ) {
            updateBoard(moveTo+17,moveTo);
        }
        else if (squares[moveTo-15] == 'N' ) {
            updateBoard(moveTo-15,moveTo);
        }
    }




}

void Chessboard::updateBoard(int pieceFrom, int pieceTo) {
    if (pieceFrom < 0 || pieceTo > 63) {
        std::cout << "ERROR movePiece out of bounds: " << pieceFrom << " " << pieceTo << "\n";
    }
    char pieceMoving = squares[pieceFrom];
    squares[pieceFrom] = ' ';
    squares[pieceTo] = pieceMoving;


}
