#ifndef POS_FIXED_H
#define POS_FIXED_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>


/*!
 * Responsavel para tarnsformção da expressão em pos fixado.
*/
class Pos_fixed{
private:
    std::string m_exp;                  //!< Expressão de entrada.
    std::string result;                 //!< Espressão resultante.
    std::queue<char> m_number;
    std::stack<char> m_ope;             //!< Pilha dos operadores.
public:

    Pos_fixed(std::string exp1) : m_exp(exp1){}

    ~Pos_fixed() = default;

    bool isConvertibleToInt(std::string str);

    void pos(std::string& exp);

    bool is_number(char digit);

    bool is_oper();

    std::string return_result();


};








#endif //POS_FIXED_H