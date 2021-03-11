//
// Created by Kirill Lakhov on 3/8/2021.
//

#ifndef ARITHMETICLIB_ARITHMETIC_H
#define ARITHMETICLIB_ARITHMETIC_H
#include <cctype>
#include "Stack.h"

class TOperand{
public:
    virtual int priority() = 0;
    virtual char get_operation() = 0;
    virtual TOperand* calc(TOperand* a, TOperand* b) = 0;
    virtual int get_number() = 0;
};

class TNum : public TOperand{
protected:
    int data;
public:
    TNum(int _d);
    TNum(TNum& _v);
    TNum(char* s);
    virtual int priority();
    virtual int get_number();
    virtual char get_operation();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TOperation : public TOperand{
protected:
    char data;
public:
    TOperation(char _d);
    TOperation(TOperation& _v);
    virtual int priority();
    virtual int get_number();
    virtual char get_operation();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};


class TSub : public TOperation{
public:
    TSub(char _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TPlus : public TOperation{
public:
    TPlus(char _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TMul : public TOperation{
public:
    TMul(char _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TDiv : public TOperation{
public:
    TDiv(char _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TPow : public TOperation{
public:
    TPow(char _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TOpenBracket : public TOperation{
public:
    TOpenBracket(char _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TCloseBracket : public TOperation{
public:
    TCloseBracket(char _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TOperandFactory{
public:
    static TOperand** create(char* s, int& n);
    static TNum* generate_number(char* s, int index);
    static TOperation* generate_operation(char operation);
    static int define_operand_amount(char* s);
};

class TPolish{
public:
    static int calculate(char* s);
    static void save(string name, char* s);
    static char* load(string name);
};

#endif //ARITHMETICLIB_ARITHMETIC_H
