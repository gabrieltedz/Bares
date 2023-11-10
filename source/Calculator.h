#include <iostream>
#include <stack>
#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_


class Calculator{
private: 
    std::string expression;
    std::string original_line;
    int op1;
    int op2;
    int result;
    char operation; // Declares a char variable named Operation
    std::stack<int> m_stack;
    
public:
    void receive_expression(std::string expression, std::string original_line);
    int calculate();
    int isConvertibleToInt(std::string str);
    bool is_number(char digit);
    

};

#endif 