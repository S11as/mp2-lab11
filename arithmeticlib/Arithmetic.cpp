//
// Created by Kirill Lakhov on 3/8/2021.
//

#include <math.h>
#include <cstring>
#include <iostream>
#include "Arithmetic.h"
#include "Functions.h"

TOperand **TOperandFactory::create(char *s, int &amount) {
    auto **result = new TOperand *[TOperandFactory::define_operand_amount(s)];
    int length = strlen(s);
    int result_index = 0;
    int str_index = 0;
    while(str_index < length){
        if(TNum::isdigit(s[str_index])){
            // число
            result[result_index] = TOperandFactory::generate_number(s, str_index);
        }else{
            // не число (функция/операция)
            result[result_index] = TOperandFactory::generate_operation(s, str_index);
        }
        result_index++;
    }
    amount = result_index;
    return result;
}

TNum *TOperandFactory::generate_number(char *s, int& index) {
    char arr[256] = {0};
    int end_of_number = index;
    int max_length = strlen(s);
    while (end_of_number < max_length) {
        if (TNum::isdigit(s[end_of_number])) end_of_number++;
        else break;
    }
    for (int i = 0; i < end_of_number - index; i++) {
        arr[i] = s[index + i];
    }
    index = end_of_number;
    return new TNum(arr);
}

TOperand *TOperandFactory::generate_operation(char *s, int &index) {
    switch (s[index]) {
        case '(':{
            index++;
            return new TOpenBracket("(");
        }
        case ')':{
            index++;
            return new TCloseBracket(")");
        }
        case '+':{
            index++;
            return new TPlus("+");
        }
        case '-':{
            index++;
            return new TSub("-");
        }
        case '*':{
            index++;
            return new TMul("*");
        }
        case '/':{
            index++;
            return new TDiv("/");
        }
        case '^':{
            index++;
            return new TPow("^");
        }
        default:{
            if(TFunction::is_sin(s,index)){
                index+=3;
                return new TSin("sin");
            }else if(TFunction::is_cos(s,index)){
                index+=3;
                return new TCos("cos");
            }else if(TFunction::is_sqrt(s,index)){
                index+=4;
                return new TSqrt("sqrt");
            }
            else{
                throw std::invalid_argument(&"invalid character at position "[index]);
            }
        }
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

double TPolish::calculate(char *s) {
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
            // знаки операции или функции или скобки
            if (stack.is_empty()) {
                //нет других операций
                stack.push(operands[i]);
            }else if (operands[i]->is_function()) {
                // префиксная функция
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
                // бинарная операция некоторого приоритета 2, 3 + ...
                TOperand *current = stack.pop();
                if (priority > current->priority()) {
                    stack.push(current);
                    stack.push(operands[i]);
                } else {
                    while (priority <= current->priority() || current->is_function()) {
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
    TStack<TOperand*> calc_stack(n);
    for (int k = 0; k < index; ++k) {
        TOperand* current = result[k];
        if(current->priority() == -1){
            // число
            calc_stack.push(current);
        }else if(current->is_function()){
            // функция
            TOperand* a = calc_stack.pop();
            TOperand* c = current->calc(a);
            calc_stack.push(c);
        }else{
            // операция
            TOperand* a = calc_stack.pop();
            TOperand* b = calc_stack.pop();
            TOperand* c = current->calc(b, a);
            calc_stack.push(c);
        }
    }
    TOperand* answer = calc_stack.pop();
    delete[] operands;
    delete[] result;
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
