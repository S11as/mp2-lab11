#include <iostream>
#include "Arithmetic.h"

int main() {
//    char* s = "3^3*(444+555)";
//    char* ss = "1.324*5-3.2";
//    (5+33)*5.33-7*cos(0.12)-sqrt(sin(0.25))
    char* sss = "(5+33)*5.33-7*cos(0.12)";
    std::cout<<TPolish::calculate(sss)<<std::endl;
    return 0;
}
