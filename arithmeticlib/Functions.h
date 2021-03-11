//
// Created by Kirill on 3/11/2021.
//

#ifndef ARITHMETICLIB_FUNCTIONS_H
#define ARITHMETICLIB_FUNCTIONS_H
#include "Operations.h"

class TFunction : public TOperand{
public:
    std::string data;
    int priority() override;
    std::string get_operation() override;
    double get_number() override;
    bool is_function() override;
    static bool is_sin(char*s, int index);
    static bool is_cos(char*s, int index);
    static bool is_sqrt(char*s, int index);
};


class TSin : public TFunction{
public:
    explicit TSin(std::string _s);
    TOperand* calc(TOperand* a) override;
};

class TCos : public TFunction {
public:
    explicit TCos(std::string _s);
    TOperand* calc(TOperand* a) override;
};

class TSqrt : public TFunction{
public:
    explicit TSqrt(std::string _s);
    TOperand* calc(TOperand* a) override;
};

#endif //ARITHMETICLIB_FUNCTIONS_H
