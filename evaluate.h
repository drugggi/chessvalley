#ifndef EVALUATE_H
#define EVALUATE_H

class Evaluate {
    private:

    public:
        Evaluate();
        ~Evaluate();

        static float eval(const std::array<char,64> *charBoard); 
};

#endif
