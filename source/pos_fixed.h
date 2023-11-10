#ifndef POS_FIXED_H
#define POS_FIXED_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>


/*!
 * @brief Responsible for transformation of expression im posfixed.
*/
class Pos_fixed{
private:
    std::string m_exp;                  //!< Input expression
    std::string result;                 //!< Resulting expression Espressão resultante.
    std::queue<char> m_number;          //!< Queue of numbers
    std::stack<char> m_ope;             //!< Stack of operators 
public:

    /**
     * @brief Constructor
     * @param exp1 m_exp will take exp1
    */
    Pos_fixed(std::string exp1) : m_exp(exp1){} 

    /**
     * @brief Deconstructor
    */
    ~Pos_fixed() = default;

    /**
     * @brief Checks if the string is convertible to int
     * @param str string to be checked if can be converted to int
    */
    bool isConvertibleToInt(std::string str);  

    /**
     * @brief Converts the infixed expression to posfixed
     * @param exp infixed expression to be converted to pos
    */
    void pos(std::string& exp);

    /**
     * @brief Checks if the char is a digit
     * @param digit char variable to be checked if its a digit
    */
    bool is_number(char digit);

    /**
     * @brief Returns the result string variable
     * @return result expression posfixed
    */
    std::string return_result();

    /**
     * @brief Resets the class
    */
    void clear();


};








#endif //POS_FIXED_H