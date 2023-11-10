#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <string>
#include "pos_fixed.h"


void Pos_fixed::pos(std::string& exp){
    // Itera através da expressão infix
    for(size_t i{0}; i < m_exp.length(); i++){
        // Se o caractere atual for um número, adiciona à pilha de números
        // '@ é usado para representar que há um número inteiro imediatamente após
        if(m_exp[i] == '@'){
            m_number.push('@');
            std::string aux;
            i++;
            // Coloque em aux o char imediatamente após '@'
            // Nesse caso pode ser um menos ou um número positive incluindo o zero
            aux = m_exp[i];
            m_number.push(m_exp[i]);
            // Avance mais um caracter
            i++;
            while(true){
                // Se o caracter for número, adicione-o a aux
                if (is_number(m_exp[i])){
                    aux += m_exp[i];
                    m_number.push(m_exp[i]);
                } 
                // Se não, pare o loop e retroceda 1 char (o loop do for irá acrescentar no final)
                else {
                    i--;
                    break;
                }
                i++;
            }
            //std::cout << aux << std::endl;
            //int m_num = stoi(aux);
            //m_number.push(m_num);
            aux.clear();
        }
        else{
            // Manipula operadores e parênteses
            if(m_exp[i] == '('){
            // Se for um parêntese aberto, adiciona à pilha de operadores
                m_ope.push(m_exp[i]);

            } 
            // Se for um parêntese fechado, move os números e operadores para a string resultante
            else if(m_exp[i] == ')'){
                m_ope.push(m_exp[i]);
                while(!m_number.empty()){
                    result += m_number.front();
                    m_number.pop();
                }
                while (!m_ope.empty()){
                    result += m_ope.top(); m_ope.pop();
                }
            
            }
            // A crescenta na pilha
            else if(m_exp[i] == '^'){
                m_ope.push(m_exp[i]); 
            }
            // Adiciona na pilha caso não tiver operadores com grau maior ou igual de preferência, se não, concatena na string.
            else if(m_exp[i] == '*'){
                if(m_ope.empty() or m_ope.top() == '+' or m_ope.top() == '-' or m_ope.top() == '('){
                    m_ope.push(m_exp[i]);

                }
                else if(m_ope.top() == '^' or m_ope.top() == '*' or m_ope.top() == '/' or m_ope.top() == '%' or m_ope.top() == ')'){
                    while(!m_number.empty()){
                        result += m_number.front();
                        m_number.pop();
                    }
                    while (!m_ope.empty() and m_ope.top() != '+' and m_ope.top() != '-'){
                        result += m_ope.top(); m_ope.pop();
                    }
                    m_ope.push(m_exp[i]);                    
                }

            }
            // Adiciona na pilha caso não tiver operadores com grau maior ou igual de preferência, se não, concatena na string.
            else if(m_exp[i] == '/') {
                if(m_ope.empty() or m_ope.top() == '+' or m_ope.top() == '-' or m_ope.top() == '('){
                    m_ope.push(m_exp[i]);

                }
                else if(m_ope.top() == '^' or m_ope.top() == '*' or m_ope.top() == '/' or m_ope.top() == '%' or m_ope.top() == ')'){
                    while(!m_number.empty()){
                        result += m_number.front();
                        m_number.pop();
                    }
                    while (!m_ope.empty() and m_ope.top() != '+' and m_ope.top() != '-'){
                        result += m_ope.top(); m_ope.pop();
                    }
                    m_ope.push(m_exp[i]);                    
                }

            }
            // Adiciona na pilha caso não tiver operadores com grau maior ou igual de preferência, se não, concatena na string.
            else if (m_exp[i] == '%'){
                if(m_ope.empty() or m_ope.top() == '+' or m_ope.top() == '-' or m_ope.top() == '('){
                    m_ope.push(m_exp[i]);

                }
                else if(m_ope.top() == '^' or m_ope.top() == '*' or m_ope.top() == '/' or m_ope.top() == '%' or m_ope.top() == ')'){
                    while(!m_number.empty()){
                        result += m_number.front();
                        m_number.pop();
                    }
                    while (!m_ope.empty() /*or m_ope.top() != '+' or m_ope.top() != '-'*/){
                        result += m_ope.top(); m_ope.pop();
                    }
                    m_ope.push(m_exp[i]);                    
                }

            }
            // Adiciona na pilha se estiver estiver vazia, se não, concatena na string.
            else if(m_exp[i] == '-'){
                if(m_ope.empty() or m_ope.top() == '('){
                    m_ope.push(m_exp[i]);
                }
                else{
                    while(!m_number.empty()){
                        result += m_number.front();
                        m_number.pop();
                    }
                    while (!m_ope.empty()){
                        result += m_ope.top(); m_ope.pop();
                    }
                    m_ope.push(m_exp[i]);
                }

            }
             // Adiciona na pilha se estiver estiver vazia, se não, concatena na string.
            else if(m_exp[i] == '+'){
                if(m_ope.empty()or m_ope.top() == '('){
                    m_ope.push(m_exp[i]);
                }                                
                else{
                    while(!m_number.empty()){
                        result += m_number.front();
                        m_number.pop();
                    }
                    while (!m_ope.empty()){
                        result += m_ope.top(); m_ope.pop();
                    }
                    m_ope.push(m_exp[i]);
                    
                }

            }
        }
    }
    // Limpa as pilhas e remove parênteses redundantes da string resultante
    while(!m_number.empty()){
        result += m_number.front();
        m_number.pop();
    }

    while(!m_ope.empty()){
        result += m_ope.top();
        m_ope.pop();
    } 

    // Remove parênteses da string resultante
    for (size_t i = 0; i < result.length(); i++){
        if (result[i] == '(' || result[i] == ')'){
            result.erase(i, 1);
            i--;
        }
        
    }
               
    std::cout << "teste " << result <<  "\n";
}

bool Pos_fixed::is_number(char digit){
    return std::isdigit(static_cast<unsigned char>(digit)) != 0;
}

bool Pos_fixed::isConvertibleToInt(std::string str){
    try {
            std::stoi(str);
            return true;
        } catch (const std::invalid_argument& e) {
            // The string is not a valid integer.
            return false;
        } catch (const std::out_of_range& e) {
            // The string is convertible to an integer, but it's out of the valid range for int.
            return false;
        }
}

std::string Pos_fixed::return_result(){
    return result;
}