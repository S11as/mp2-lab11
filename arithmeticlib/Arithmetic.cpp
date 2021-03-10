//
// Created by Kirill Lakhov on 3/8/2021.
//

#include <math.h>
#include <cstring>
#include "Arithmetic.h"

TNum::TNum(int _d) {
    this->data = _d;
}

TNum::TNum(TNum &_v) {
    this->data = _v.data;
}

int TNum::priority() {
    return -1;
}

int TNum::get_number() {
    return this->data;
}

char TNum::get_operation() {
    throw "cant get operation of a num";
}

TOperand *TNum::calc(TOperand *a, TOperand *b) {
    throw "cant calculate a num";
}

TNum::TNum(char *s) {
    int i = 0;
    while (isdigit(s[i])) {
        i++;
    }
    if (s[i] != 0) {
        throw -1;
    }
    this->data = atof(s);
}


TOperation::TOperation(char _d) {
    this->data = _d;
}

TOperation::TOperation(TOperation &_v) {
    this->data = _v.data;
}

int TOperation::priority() {
    return -1;
}

int TOperation::get_number() {
    throw "cant get a number from operation";
}

char TOperation::get_operation() {
    return this->data;
}

TOperand *TOperation::calc(TOperand *a, TOperand *b) {
    throw "cant calculate a num";
}

TSub::TSub(char _d) : TOperation(_d) {}

int TSub::priority() {
    return 2;
}

TOperand *TSub::calc(TOperand *a, TOperand *b) {
    TNum *res = new TNum(a->get_number() - b->get_number());
    return res;
}

TPlus::TPlus(char _d) : TOperation(_d) {}

int TPlus::priority() {
    return 2;
}

TOperand *TPlus::calc(TOperand *a, TOperand *b) {
    TNum *res = new TNum(a->get_number() + b->get_number());
    return res;
}

TMult::TMult(char _d) : TOperation(_d) {}

int TMult::priority() {
    return 3;
}

TOperand *TMult::calc(TOperand *a, TOperand *b) {
    TNum *res = new TNum(a->get_number() * b->get_number());
    return res;
}

TDiv::TDiv(char _d) : TOperation(_d) {}

int TDiv::priority() {
    return 3;
}

TOperand *TDiv::calc(TOperand *a, TOperand *b) {
    if (b->get_number() == 0)
        throw "division by 0 error";
    TNum *res = new TNum(a->get_number() / b->get_number());
    return res;
}


TOpenBracket::TOpenBracket(char _d) : TOperation(_d) {}

int TOpenBracket::priority() {
    return 1;
}

TOperand *TOpenBracket::calc(TOperand *a, TOperand *b) {
    throw "open bracket calculation";
}

TCloseBracket::TCloseBracket(char _d) : TOperation(_d) {}

int TCloseBracket::priority() {
    return 1;
}

TOperand *TCloseBracket::calc(TOperand *a, TOperand *b) {
    throw "close bracket calculation";
}


TOperand **TOperandFactory::create(char *s, int &non_digit) {
    int length = strlen(s);
    for (int i = 0; i < length; i++) {
        if (isdigit(s[i])) non_digit++;
    }
    int operands = (non_digit + 1) * 2 - 1;
    auto** result = new TOperand*[operands];
    int start = 0;
    int j = 0;

}
