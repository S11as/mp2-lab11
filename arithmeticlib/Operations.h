//
// Created by Kirill on 3/11/2021.
//

#ifndef ARITHMETICLIB_OPERATIONS_H
#define ARITHMETICLIB_OPERATIONS_H
#include <math.h>
#include <cstring>
#include <iostream>

class TOperand{
public:
    virtual int priority() = 0;
    virtual std::string get_operation() = 0;
    virtual double get_number() = 0;
    virtual bool is_function();
    virtual TOperand* calc(TOperand* a);
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TNum : public TOperand{
protected:
    double data;
public:
    TNum(double _d);
    TNum(TNum& _v);
    TNum(char* s);
    static bool isdigit(char c);
    int priority() override;
    double get_number() override;
    std::string get_operation() override;
    TOperand* calc(TOperand* a, TOperand* b) override;
};


class TOperation : public TOperand{
protected:
    std::string data;
public:
    TOperation(std::string _d);
    TOperation(TOperation& _v);
    int priority() override;
    std::string get_operation() override;
    double get_number() override;
};

class TSub : public TOperation{
public:
    TSub(std::string _d);
    int priority() override;
    virtual TOperand* calc(TOperand* a, TOperand* b) override;
};

class TPlus : public TOperation{
public:
    TPlus(std::string _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TMul : public TOperation{
public:
    TMul(std::string _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TDiv : public TOperation{
public:
    TDiv(std::string _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TPow : public TOperation{
public:
    TPow(std::string _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TOpenBracket : public TOperation{
public:
    TOpenBracket(std::string _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};

class TCloseBracket : public TOperation{
public:
    TCloseBracket(std::string _d);
    virtual int priority();
    virtual TOperand* calc(TOperand* a, TOperand* b);
};



#endif //ARITHMETICLIB_OPERATIONS_H
