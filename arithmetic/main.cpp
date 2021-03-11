#include <iostream>
#include "Arithmetic.h"

int main() {
    char* s = "3*(444+555)";
    TPolish::calculate(s);
    return 0;
}
