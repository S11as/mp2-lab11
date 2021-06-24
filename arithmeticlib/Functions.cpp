//
// Created by Kirill on 3/11/2021.
//

#include "Functions.h"

bool TFunction::is_function() {
    return true;
}

bool TFunction::is_sin(char *s, int index) {
    int length = strlen(s);
    if (index + 3 >= length) return false;
    return s[index] == 's' && s[index + 1] == 'i' && s[index + 2] == 'n';
}

bool TFunction::is_cos(char *s, int index) {
    int length = strlen(s);
    if (index + 3 >= length) return false;
    return s[index] == 'c' && s[index + 1] == 'o' && s[index + 2] == 's';
}

bool TFunction::is_sqrt(char *s, int index) {
    int length = strlen(s);
    if (index + 4 >= length) return false;
    return s[index] == 's' && s[index + 1] == 'q' && s[index + 2] == 'r' && s[index + 3] == 't';
}

std::string TFunction::get_operation() {
    return this->data;
}

int TFunction::priority() {
    return 3;
}

double TFunction::get_number() {
    return -1;
}

TSin::TSin(std::string _s) {
    this->data = _s;
}

TOperand *TSin::calc(TOperand *a) {
    return new TNum(sin(a->get_number()));
}

TCos::TCos(std::string _s) {
    this->data = _s;
}

TOperand *TCos::calc(TOperand *a) {
    return new TNum(cos(a->get_number()));
}

TSqrt::TSqrt(std::string _s) {
    this->data = _s;
}

TOperand *TSqrt::calc(TOperand *a) {
    return new TNum(sqrt(a->get_number()));
}
