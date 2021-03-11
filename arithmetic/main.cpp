#include <iostream>
#include "Arithmetic.h"

int main() {
    char* s = "3*(444+555)";
    TPolish::save("output.txt",s);
    TPolish::load("output.txt");
    return 0;
}
