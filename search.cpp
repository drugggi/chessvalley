#include <iostream>
#include <vector>
#include <array>
#include "chessboard.h"
#include "bitboards.h"
#include "pieceinfo.h"
#include "search.h"

Search::Search() {

}
Search::~Search() {

}

void Search::searchNextMoves() {


}
float Search::getEval() {
    if (nextMoveSearch.size() == 0 ) {
        return eval;
    }
    else {
        return nextMoveSearch.at(0).getEval();
    }
}
