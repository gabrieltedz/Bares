#include <iostream>
#include <stack>
#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_


class Calculator{
private: 
    std::string expression;     //!< Posfixed_expression
    std::string original_line;  //!< Original line
    int op1{0};                 //!< Operand 1
    int op2{0};                 //!< Operand 2 
    int result{0};              //!< Result of operation
    std::stack<int> m_stack;    //!< Stack of int numbers
    
public:
    /**
     * @brief Receive @param expression (posfixed) and the @param original_line with the original line
    */
    void receive_expression(std::string expression, std::string original_line);
    
    /**
     * @brief Calculate the result of the entire expression
    */
    int calculate();

    /**
     * @brief verify is @param str is convertible to int
    */
    int isConvertibleToInt(std::string str);

    /**
     * @brief verify if @param digit is a number
    */
    bool is_number(char digit);

    /**
     * @brief Reset the class
    */
    void clear();

};

#endif 