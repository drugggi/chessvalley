#include <iostream>
#include <string>
#include "chessboard.h"

int main(int argc, const char* argv[] ) {

    Chessboard *pChessboard = new Chessboard();

   pChessboard->printChessboard(); 

   std::string *pCommand = new std::string {"huh"};

   while (*pCommand != "q") {

       std::cout << "give a move command or 'q' to quit" << "\n";
       pChessboard->printChessboard();
       std::cin >> *pCommand;
       while ( pChessboard->moveCommand(*pCommand) == false && *pCommand != "q") {
           std::cout << "false command: " << *pCommand << "\n";
           std::cin >> *pCommand;
       }
   }
   


    return EXIT_SUCCESS;
}
