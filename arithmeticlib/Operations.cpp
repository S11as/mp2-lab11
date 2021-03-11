//
// Created by Kirill on 3/11/2021.
//

#include "Operations.h"

bool TOperand::is_function() {
    return false;
}

TOperand* TOperand::calc(TOperand* a){
    return nullptr;
}

TOperand *TOperand::calc(TOperand *a, TOperand *b) {
    return nullptr;
}

double TOperand::get_number() {
    return -1;
}

TNum::TNum(double _d) {
    this->data = _d;
}

TNum::TNum(TNum &_v) {
    this->data = _v.data;
}

int TNum::priority() {
    return -1;
}

double TNum::get_number() {
    return this->data;
}

std::string TNum::get_operation() {
    return "num";
}

TOperand *TNum::calc(TOperand *a, TOperand *b) {
    throw "cant calculate a num";
}


TNum::TNum(char *s) {
    int i = 0;
    while (TNum::isdigit(s[i])) {
        i++;
    }
    if (s[i] != 0) {
        throw std::invalid_argument("cant parse");
    }
    this->data = atof(s);
}

bool TNum::isdigit(char c) {
    if(c == '.') return true;
    return std::isdigit(c);
}


TOperation::TOperation(std::string _d) {
    this->data = _d;
}

TOperation::TOperation(TOperation &_v) {
    this->data = _v.data;
}

int TOperation::priority() {
    return -1;
}

std::string TOperation::get_operation() {
    return this->data;
}

double TOperation::get_number() {
    return -1;
}


TSub::TSub(std::string _d) : TOperation(_d) {}

int TSub::priority() {
    return 2;
}

TOperand *TSub::calc(TOperand *a, TOperand *b) {
    TNum *res = new TNum(a->get_number() - b->get_number());
    return res;
}

TPlus::TPlus(std::string _d) : TOperation(_d) {}

int TPlus::priority() {
    return 2;
}

TOperand *TPlus::calc(TOperand *a, TOperand *b) {
    TNum *res = new TNum(a->get_number() + b->get_number());
    return res;
}

TMul::TMul(std::string _d) : TOperation(_d) {}

int TMul::priority() {
    return 3;
}

TOperand *TMul::calc(TOperand *a, TOperand *b) {
    TNum *res = new TNum(a->get_number() * b->get_number());
    return res;
}

TDiv::TDiv(std::string _d) : TOperation(_d) {}

int TDiv::priority() {
    return 3;
}

TOperand *TDiv::calc(TOperand *a, TOperand *b) {
    if (b->get_number() == 0)
        throw "division by 0 error";
    TNum *res = new TNum(a->get_number() / b->get_number());
    return res;
}

TPow::TPow(std::string _d) : TOperation(_d) {}

int TPow::priority() {
    return 4;
}

TOperand *TPow::calc(TOperand *a, TOperand *b) {
    int power = b->get_number();
    int number = a->get_number();
    int res = number;
    if (power == 0) {
        res = 1;
    } else {
        for (int i = 1; i < power; ++i) {
            res *= number;
        }
    }
    return new TNum(res);
}


TOpenBracket::TOpenBracket(std::string _d) : TOperation(_d) {}

int TOpenBracket::priority() {
    return 1;
}

TOperand *TOpenBracket::calc(TOperand *a, TOperand *b) {
    throw "open bracket calculation";
}

TCloseBracket::TCloseBracket(std::string _d) : TOperation(_d) {}

int TCloseBracket::priority() {
    return 0;
}

TOperand *TCloseBracket::calc(TOperand *a, TOperand *b) {
    throw "close bracket calculation";
}
