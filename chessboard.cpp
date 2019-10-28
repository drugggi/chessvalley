#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "chessboard.h"
#include "bitboards.h"
#include "search.h"

Chessboard::Chessboard() {
    bbs = new Bitboards(SQ,whitesTurn);    
    whiteSpecialMoves = new SpecialMoves{{0,0}, true, true};
    blackSpecialMoves = new SpecialMoves{{0,0}, true, true};
}

Chessboard::~Chessboard() {
    delete bbs;
}
void Chessboard::computerTriesToCalculateMoves() {

    Search computerThinks{SQ,whitesTurn};
    computerThinks.evaluateCurrentBoard(SQ,whitesTurn);
    whitesTurn = !whitesTurn;
    /*
    Bitboards currentBoard {SQ, whitesTurn};
    std::cout << "huge hefner " ;
    std::vector<PieceInfo> blackPieces = currentBoard.getBlackPieces();
    
    std::vector<int> moves;
    int pieceFrom;
    int pieceTo;
    float bestEval=100;
    std::vector<Search> testingSearch;
    std::cout << "fug";
    for (int i = 0; i < blackPieces.size() ; i++) {
        std::cout << "loselosesitutation ";

        if (blackPieces.at(i).getLegalMoves().any() ) {
            moves = blackPieces.at(i).getLegalMoveSquares();
            pieceFrom = blackPieces.at(i).getSquare();
            std::cout<<"inittowinit";

            for (int j = 0; j < moves.size() ; j++) {
                pieceTo = moves.at(j);
                Search temp {SQ, pieceFrom, pieceTo, whitesTurn};
                testingSearch.push_back(temp);

            }

        }
    }
 //   std::cout <<pieceFrom <<  "searching ends" << pieceTo <<  "\n";
  //  std::cout << "testingSearch.size(): " << testingSearch.size();
    std::cout <<"heh";
    for (int i = 0 ; i < testingSearch.size() ; i++) {
        testingSearch.at(i).searchNextMoves(SQ, whitesTurn);
    }
    std::cout << "huh\n";
    std::cout <<"in\n";
    std::cout << "out\n";
    movePiece(pieceFrom,pieceTo);

    whitesTurn = true;
    */
}
void Chessboard::computerMovesNonRandomly() {

    // Search findBestMove {SQ,whitesTurn};
    int moveFrom;
    int moveTo;
    
    std::cout << "searching started!" << "\n";

    Bitboards currentBoard {SQ, whitesTurn};
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
                SQ[startingSquare] = ' ';
                char tempPiece = SQ[moves.at(j) ];
                SQ[moves.at(j) ] = movingPiece;

                Bitboards evalBoard {SQ, !whitesTurn};
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
                SQ[startingSquare] = movingPiece;
                SQ[moves.at(j) ] = tempPiece;

            }
        }
    }

    movePiece(moveFrom , moveTo );
    
    whitesTurn = true;
    // computerMovesRandomly();
}
void Chessboard::computerMovesRandomly() {

    std::vector<PieceInfo> blackPieces = bbs->getBlackPieces();
    int allPieces = blackPieces.size();

    std::srand(std::time(nullptr) );
    int random_piece = std::rand() % allPieces;

    // std::cout << "pieces.size(): " << allPieces << "  rand: " << random_piece << "\n";

    int idiotCounter = 0;
    while ( random_piece < blackPieces.size() ) {

        if (blackPieces.at(random_piece).getLegalMoves().any() ) {
            blackPieces.at(random_piece).printPieceInfo();
            break;

        }
        else {
            blackPieces.at(random_piece).printPieceInfo();
        }

        random_piece++;
        if (random_piece == blackPieces.size() ) {
            random_piece = 0;
        }
        idiotCounter++;
        if (idiotCounter > 100) {
            std::cout << "idiot counter achieved... Stalemate? " << "\n";
            return;
        }
    }
//    std::cout << "values W: " << bbs->countWhiteMaterial() << " B: " << bbs->countBlackMaterial() << "\n";    
    std::vector<int> moves = blackPieces.at(random_piece).getLegalMoveSquares();
    int random_move = std::rand() % moves.size();
    // std::cout << "moves.size(): " << moves.size() << "  rand: " << random_move << "\n";
    movePiece(blackPieces.at(random_piece).getSquare() , moves.at(random_move) );
    
    whitesTurn = true;
}
const void Chessboard::printBoardPieces() {
    std::vector<PieceInfo> whitePieces = bbs->getWhitePieces();
    std::vector<PieceInfo> blackPieces = bbs->getBlackPieces();

    for (int i = 0; i < whitePieces.size() ; i++ ) {
        whitePieces.at(i).printPieceInfo();
    }
    for (int i = 0; i < blackPieces.size() ; i++ ) {
        blackPieces.at(i).printPieceInfo();
    }

}
std::string Chessboard::coordinate(int square) {
    int file = square % 8;
    int rank = (square / 8-8)*-1;

    char charFile = (char)(file + 65);
    char charRank = (char)(rank + 48);

    std::string coordinate= std::string()+ charFile + charRank;
    return coordinate;
}
const void Chessboard::printChessboard() {

    // printing chessboard, first row starts with white squre
    // next row starts with black square, odd variable takes care of that
    int odd = 0;
    int square = 0;
    // chess board ranks 1-8
    for (int rank = 0 ; rank < 8 ; rank++) {
        // chess board files A-H, every file consists of three console rows
        for (int row = 0; row < 3 ; row++) {
            for (int file = 0 ; file < 8 ; file++) {
                // piece info (char) into middle of square
                if ( row == 1) {
                    square = rank * 8 + file;
                    char piece = SQ[square];
                    if( (int) SQ[square] >= (int)'a') {
                        piece = SQ[square]-32;
                    }
                    // no need to keep black pieces undercase, black pieces are represented as red
                    std::string p = std::string() + piece + piece;
                    if (SQ[square] == 'p' || SQ[square] == 'P') {
                        p =std::string() +  piece +" ";
                    }
                    
                    // piece that user has selected is represented as green color
                    if (highlightSquare == square ) {
                        if (file % 2 == odd) {

                        std::cout << "\033[0;100m  \033[1;32m" << p << "  \033[0m";
                        } else {
                            std::cout << "  \033[1;32m" << p << "  ";
                        }

                    }
                    // black piece (red color)
                    else if ((int)SQ[square] > 96 && (int)SQ[square] < 123 ) {
                        if (file % 2 == odd) {

                        std::cout << "\033[0;100m  \033[1;31m" << p << "  \033[0m";
                        } else {
                            std::cout << "  \033[1;31m" << p << "  ";
                        }
                    } // white piece (white color)
                    else {

                        if (file % 2 == odd) {

                        std::cout << "\033[0;100m  " << p << "  \033[0m";
                        } else {
                            std::cout << "  " << p << "  ";
                        }
                    }
                }
                else {
                    if (file % 2 == odd) {
                    std::cout << "\033[0;100m      \033[0m";
                    } else {
                        std::cout << "      ";
                    }
                }
            }
            std::cout << "\n";
        }
        if (odd == 0 ) {
            odd = 1;
        } else { odd = 0; }

 //       std::cout << "\n";

    }
}
bool Chessboard::moveCommand(std::string command) {

    int square = getSquare(command);
  //  std::cout << command << " and square: " << square << "\n";

    if (command == "history") {
        printMoveHistory();
        return false;
    }
    if (square < 0 || square > 63) {
        return false;
    }
    if (square == highlightSquare) {
        highlightSquare = -1;
    }
    else if (highlightSquare != -1) {
       // std::cout << "move command from: "<< highlightSquare << " to: " << square << "\n";
        std::bitset<64> legalMoves = bbs->getLegalMoves(highlightSquare);//, SQ[highlightSquare]);
        if ( legalMoves[square] == 1 ) {
            movePiece(highlightSquare,square);
            whitesTurn = false;
            highlightSquare = -1;
        }
        else {
            std::cout << "illegal move piece: " << SQ[highlightSquare] << " to: " << square;
        }
    }
    else if (SQ[square] == ' ' && highlightSquare == -1) {
        std::cout << "Cannot highlight empty square: " << square << "\n";
    }

    else {
        std::cout << "piece there is: '" << SQ[square] << "'\n";
        std::cout << "highlight command" << "\n";
        highlightSquare = square;
        std::bitset<64> legalMoves = bbs->getLegalMoves(square);//, SQ[square] );
        bbs->printBitboard(legalMoves);
    }

    return true;
}
void Chessboard::movePiece(int from, int to) {
    
    if (SQ[from] == 'P' && to < 8) {
        std::cout << "automatic promotion, change this in future\n";
        SQ[from] = 'Q';
    }
    else  if ( SQ[from] == 'p' && to > 55 ) {
       SQ[from] = 'q';
    } 

    if (SQ[from] == 'P' && (from - to) == 16) {
        if (from == 48) {blackSpecialMoves->enPassant[1] = 33; }
        else if (from == 55) {blackSpecialMoves->enPassant[0] = 38; }
        else { blackSpecialMoves->enPassant[0] = to-1;
            blackSpecialMoves->enPassant[1] = to+1;
        }
        std::cout <<  "allow en passant for black! squares" << blackSpecialMoves->enPassant[0]
           << " and " << blackSpecialMoves->enPassant[1] << "  \n";
    }
    else if  (SQ[from] == 'p' && (from - to) == -16 ) {
        if (from == 8) {whiteSpecialMoves->enPassant[1] = 25; }
        else if (from == 15) {whiteSpecialMoves->enPassant[0] = 30; }
        else { whiteSpecialMoves->enPassant[0] = to-1;
            whiteSpecialMoves->enPassant[1] = to+1;
        }
        std::cout <<  "allow en passant for white! squares" << whiteSpecialMoves->enPassant[0]
           << " and " << whiteSpecialMoves->enPassant[1] << "  \n";
    }
    else {
        blackSpecialMoves->enPassant[0] = 0;
        blackSpecialMoves->enPassant[1] = 0;
        whiteSpecialMoves->enPassant[0] = 0;
        whiteSpecialMoves->enPassant[1] = 0;
    }
    if (SQ[from] == 'K' ) {
        std::cout << "King moved castling disallowed";
        whiteSpecialMoves->castleKingside = false;
        whiteSpecialMoves->castleQueenside = false;
    }
    else if (SQ[from] == 'k' ) {
        std::cout << "black king moved, castling disallowed";
        blackSpecialMoves->castleKingside = false;
        blackSpecialMoves->castleQueenside = false;
    }
    if ((from == 63 || from == 56 ) && SQ[from] == 'R') {
        if ( from == 56 ) {whiteSpecialMoves->castleQueenside = false; }
        if ( from == 63 ) {whiteSpecialMoves->castleKingside = false; }
    }
    else if ((from == 0 || from == 7 ) && SQ[from] == 'r') {
        if ( from == 0 ) {blackSpecialMoves->castleQueenside = false; }
        if ( from == 7 ) {blackSpecialMoves->castleKingside = false; }
    }
    std::cout << "castling rights bqs: "
        << blackSpecialMoves->castleQueenside << " bks " << blackSpecialMoves->castleKingside
        << " wQs " << whiteSpecialMoves->castleQueenside <<
        " wKs "<< whiteSpecialMoves->castleKingside << "\n";
    SQ[to] = SQ[from];
    SQ[from] = ' ';
    
    // Huge pain in the ass was tracking the bug where it was wrong color to move
    // !whitesTurn seems to be working so far
    delete bbs;
     bbs = new Bitboards(SQ,!whitesTurn);
    moveHistory.push_back(from);
    moveHistory.push_back(to);
}
bool Chessboard::isWhitesTurn() {
    return whitesTurn;
}

int Chessboard::getSquare(std::string coordinate) {

    if (coordinate.length() == 2) {
        char file = coordinate[0];
        char rank = coordinate[1];
//        std::cout << file << ":" << (int)file << "  " << rank << ":" << (int) rank << "\n";
        int rankNro =( (int) rank - 56)*-1;
        int fileNro = (int) file - 97;

 //       std::cout << "square: " << (rankNro * 8 + fileNro) << "\n";
        return (rankNro * 8 + fileNro);
    }

}

const void Chessboard::printMoveHistory() {
    for (int i = 0 ; i < moveHistory.size() ; i++) {
        std::cout << coordinate(moveHistory.at(i)) << "->";
        i++;
        std::cout << coordinate(moveHistory.at(i)) << "  |  ";
        i++;
        if (i >= moveHistory.size()) {break; }
        std::cout << coordinate(moveHistory.at(i)) << "->";
        i++;
        std::cout << coordinate(moveHistory.at(i)) << "\n";
    }

}
/*
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
    std::vector<char> commandChars; 
    for (int i = 0 ; i < command.length() ; i++) {
        commandChars.push_back( command.at(i) );
    }
    char file = commandChars.at( commandChars.size() - 2);
    char rank = commandChars.at( commandChars.size() -1);

    int moveTo = (( (int) rank-56)*-8) + ( (int) file-97 );
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

    if (piece == 'K') {
        int moveFrom = whereIsPiece('K');
        std::bitset<64> testKing = bbs->getWhiteKingMoves(moveFrom);
        bbs->printBitboard(testKing);
        if (testKing[moveTo] == 1 ) {
            std::cout << "allowed move apparently" << "\n";
        }
    }
    if (piece == 'P') {
        if (SQ[moveTo+8] == 'P') {
           updateBoard(moveTo+8 , moveTo); 

        } 
        else if (moveTo > 31 % moveTo < 40 && SQ[moveTo+16] == 'P' ){
            updateBoard(moveTo+16,moveTo);
        }

     }

    if (piece == 'N') {
        if (SQ[moveTo+15] == 'N' ) {
            updateBoard(moveTo+15,moveTo); 
        }
        else if (SQ[moveTo+17] == 'N' ) {
            updateBoard(moveTo+17,moveTo);
        }
        else if (SQ[moveTo-15] == 'N' ) {
            updateBoard(moveTo-15,moveTo);
        }
    }

}
*/
int Chessboard::whereIsPiece(char piece) {
    for (int i = 0 ; i < SQ.size() ; i++) {
        if (SQ.at(i) == piece) {
            return i;
        }
    }
    return 0;
}
void Chessboard::updateBoard(int pieceFrom, int pieceTo) {
    if (pieceFrom < 0 || pieceTo > 63) {
        std::cout << "ERROR movePiece out of bounds: " << pieceFrom << " " << pieceTo << "\n";
    }
    char pieceMoving = SQ[pieceFrom];
    SQ[pieceFrom] = ' ';
    SQ[pieceTo] = pieceMoving;

    delete bbs;
    bbs = new Bitboards(SQ,whitesTurn);

}
