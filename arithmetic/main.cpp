#include <iostream>
#include "Arithmetic.h"

int main() {
    char* s = "3^3*(444+555)";
    TPolish::calculate(s);
//    TPolish::save("output.txt",s);
//    TPolish::load("output.txt");
    return 0;
}
