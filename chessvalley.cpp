#include <iostream>
#include <string>
#include "chessboard.h"

int main(int argc, const char* argv[] ) {

    Chessboard *pChessboard = new Chessboard();
    std::string command;

   while (command != "q") {

       if (pChessboard->isWhitesTurn() ) {
           std::cout << "give a move command or 'q' to quit" << "\n";
           pChessboard->printChessboard();
           std::cin >> command;
           if ( pChessboard->moveCommand(command) == false && command != "q") {

               std::cout << "false command: " << command << "\n";
               std::cin >> command;
           }
       }
       else {
           pChessboard->computerMovesRandomly();
       }
   }
   delete pChessboard;

    return EXIT_SUCCESS;
}
