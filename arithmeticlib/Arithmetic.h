//
// Created by Kirill Lakhov on 3/8/2021.
//

#ifndef ARITHMETICLIB_ARITHMETIC_H
#define ARITHMETICLIB_ARITHMETIC_H
#include <cctype>
#include "Stack.h"

#include "Operations.h"



class TOperandFactory{
public:
    static TOperand** create(char* s, int& n);
    static TNum* generate_number(char* s, int& index);
    static TOperand* generate_operation(char *s, int& index);
    static int define_operand_amount(char* s);
};

class TPolish{
public:
    static double calculate(char* s);
    static void save(string name, char* s);
    static char* load(string name);
};

#endif //ARITHMETICLIB_ARITHMETIC_H
