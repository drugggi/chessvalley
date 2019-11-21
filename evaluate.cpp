#include <array>
#include "evaluate.h"

Evaluate::Evaluate() {


}

Evaluate::~Evaluate() {

}

float Evaluate::eval(const std::array<char,64> *charBoard) {

    float blackMaterial=0;
    float whiteMaterial=0;
    for (int i = 0 ; i < charBoard->size() ; i++) {
        if (charBoard->at(i) == ' ') {
            continue;
        }
        else if (charBoard->at(i) == 'p') {
            blackMaterial++;
            continue;
        }
        else if (charBoard->at(i) == 'P') {
            whiteMaterial++;
            continue;
        }
        else if (charBoard->at(i) == 'r') {
            blackMaterial+=4;
            continue;
        }
        else if (charBoard->at(i) == 'R') {
            whiteMaterial+=4;
            continue;
        }
        else if (charBoard->at(i) == 'n') {
            blackMaterial+=3;
            continue;
        }
        else if (charBoard->at(i) == 'N') {
            whiteMaterial+=3;
            continue;
        }
        else if (charBoard->at(i) == 'b') {
            blackMaterial+=3;
            continue;
        }
        else if (charBoard->at(i) == 'B') {
            whiteMaterial+=3;
            continue;
        }
        else if (charBoard->at(i) == 'q') {
            blackMaterial+=6;
            continue;
        }
        else if (charBoard->at(i) == 'Q') {
            whiteMaterial+=6;
            continue;
        }

        
    }
    return whiteMaterial-blackMaterial;

}
