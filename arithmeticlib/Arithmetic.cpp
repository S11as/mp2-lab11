//
// Created by Kirill Lakhov on 3/8/2021.
//

#include <math.h>
#include <cstring>
#include <iostream>
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
    return -1;
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
    return -1;
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

TMul::TMul(char _d) : TOperation(_d) {}

int TMul::priority() {
    return 3;
}

TOperand *TMul::calc(TOperand *a, TOperand *b) {
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
    return 0;
}

TOperand *TCloseBracket::calc(TOperand *a, TOperand *b) {
    throw "close bracket calculation";
}


TOperand **TOperandFactory::create(char *s, int &amount) {
    auto **result = new TOperand *[TOperandFactory::define_operand_amount(s)];
    int length = strlen(s);
    int index = 0;
    if (!isdigit(s[0])) {
        result[index] = TOperandFactory::generate_operation(s[0]);
        index++;
    }
    for (int i = 1; i < length; i++) {
        if (!isdigit(s[i])) {
            if (isdigit(s[i - 1])) {
                result[index] = TOperandFactory::generate_number(s, i - 1);
                index++;
            }
            result[index] = TOperandFactory::generate_operation(s[i]);
            index++;
        }
    }
    amount = index;
    return result;
}

TNum *TOperandFactory::generate_number(char *s, int index) {
    char arr[256] = {0};
    int start = index;
    while (start >= 0) {
        if (isdigit(s[start])) start--;
        else break;
    }
    for (int i = 0; i < index - start; i++) {
        arr[i] = s[start + 1 + i];
    }
    return new TNum(arr);
}

TOperation *TOperandFactory::generate_operation(char operation) {
    switch (operation) {
        case '(':
            return new TOpenBracket(operation);
        case ')':
            return new TCloseBracket(operation);
        case '+':
            return new TPlus(operation);
        case '-':
            return new TSub(operation);
        case '*':
            return new TMul(operation);
        case '/':
            return new TDiv(operation);
        default:
            return nullptr;
    }
}

int TOperandFactory::define_operand_amount(char *s) {
    int length = strlen(s);
    int non_digit = 0;
    for (int i = 0; i < length; i++) {
        if (!isdigit(s[i])) non_digit++;
    }
    return (non_digit + 1) * 2 - 1;
}

int TPolish::calculate(char *s) {
    int n = 0;
    TOperand **operands = TOperandFactory::create(s, n);
    auto **result = new TOperand *[n];
    TStack<TOperand *> stack(n);
    int index = 0;
    for (int i = 0; i < n; ++i) {
        int priority = operands[i]->priority();
        if (priority == -1) {
            // число
            result[index] = operands[i];
            index++;
        } else {
            // знаки операции или скобки
            if (stack.is_empty()) {
                //нет других операций
                stack.push(operands[i]);
            } else if (priority == 1) {
                // скобки
                // открывающуюся кладем в стек
                stack.push(operands[i]);
            } else if (priority == 0) {
                // скобки
                // закрывающаяяся - идем по стеку и ищем открывающуююся, закидывая все что перед ней в выходной массив
                if (stack.is_empty())
                    throw "braces error";
                TOperand *tmp = stack.pop();
                while (tmp->priority() != 1) {
                    result[index] = tmp;
                    index++;
                    tmp = stack.pop();
                }
            } else {
                // операция некоторого приоритета 2, 3 + ...
                TOperand *current = stack.pop();
                if (priority > current->priority()) {
                    stack.push(current);
                    stack.push(operands[i]);
                } else {
                    while (priority <= current->priority()) {
                        result[index] = current;
                        index++;
                        if (!stack.is_empty()) {
                            current = stack.pop();
                        } else {
                            break;
                        }
                    }
                    if (!stack.is_empty())
                        stack.push(current);
                    stack.push(operands[i]);
                }
            }
        }
    }
    while (!stack.is_empty()) {
        TOperand *current = stack.pop();
        result[index] = current;
        index++;
    }
    for (int j = 0; j < index; ++j) {
        std::cout << result[j]->get_number() << " " << result[j]->get_operation() << std::endl;
    }
    TStack<TOperand*> calc_stack(n);
    for (int k = 0; k < index; ++k) {
        TOperand* current = result[k];
        if(current->priority() == -1){
            // число
            calc_stack.push(current);
        }else{
            TOperand* a = calc_stack.pop();
            TOperand* b = calc_stack.pop();
            TOperand* c = current->calc(a, b);
            calc_stack.push(c);
        }
    }
    TOperand* answer = calc_stack.pop();
    delete[] operands;
    delete[] result;
    std::cout<<answer->get_number()<<std::endl;
    return answer->get_number();
}

void TPolish::save(string name, char *s) {
    fstream file;
    file.open(name, fstream::out);
    if (!file.is_open())
        throw "Cant open such file";
    int n = 0;
    TOperand** res = TOperandFactory::create(s, n);
    file<<n<<"\n";
    for (int i = 0; i < n; i++)
        if (res[i]->priority() == -1)
            file << res[i]->get_number();
        else
            file << res[i]->get_operation();
    file.close();
}

char* TPolish::load(string name) {
    std::ifstream file;
    file.open(name, std::fstream::in);
    if (!file.is_open())
        throw "Cant open such file";
    int n;
    file>>n;
    char* s = new char[n];
    for (int i = 0; i < n; ++i) {
        file>>s[i];
    }
    return s;
}
