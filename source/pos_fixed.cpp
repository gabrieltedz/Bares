#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <string>
#include "pos_fixed.h"

/**
 * @brief Converts the infixed expression to posfixed
 * @param exp infixed expression to be converted to pos
*/
void Pos_fixed::pos(std::string& exp){
    // Iterate through the infixed expression
    for(size_t i{0}; i < m_exp.length(); i++){
        // If current characht is a number, add it to the stack of numbers
        // '@' is utilized here to indicate a int number immediately after

        if(m_exp[i] == '@'){
            // We send the '@' because we will also use it to indicate a integer number in the Calculator class
            m_number.push('@');
            std::string aux;
            i++;

            // Put in aux the char immediately after '@'
            // It can be either '-' or a positive number including zero
            aux = m_exp[i];
            m_number.push(m_exp[i]);


            // Advance another charachter 
            i++;

            // Stop if find a char that is not a number
            while(true){
                // If the char is a number, add it to aux
                if (is_number(m_exp[i])){
                    aux += m_exp[i];
                    m_number.push(m_exp[i]);
                } 
                // Else, stop the loop and retreat 1 char 
                // this is because the for loop will start in the right position in the next iteration
                else {
                    i--;
                    break;
                }

                // If the while loop wasnt broken, advance another char in the line
                i++;
            }
            aux.clear();
        }
        else{
            // Manipulating operators and parenthesis
            if(m_exp[i] == '('){
            // If its an open parenthesis, add it to the stack of operators
                m_ope.push(m_exp[i]);

            } 
            // If it's an closing parenthesis, move the numbers and operators to the result string
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
            
            //Add it to the stack
            else if(m_exp[i] == '^'){
                m_ope.push(m_exp[i]); 
            }

            // Add to the stack if there arent any operators with higher or equal preference, else, concatenates in the string
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
            // Add to the stack if there arent any operators with higher or equal preference, else, concatenates in the string
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
            // Add to the stack if there arent any operators with higher or equal preference, else, concatenates in the string
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
            // Add to the stack if it is empty, else, concatenates into the string
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
            // Add to the stack if it is empty, else, concatenates into the string
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

    // Clears the stacks and removes redundant parenthesis in the resulting string
    while(!m_number.empty()){
        result += m_number.front();
        m_number.pop();
    }

    while(!m_ope.empty()){
        result += m_ope.top();
        m_ope.pop();
    } 

    // Removes parenthesis from the resulting string
    for (size_t i = 0; i < result.length(); i++){
        if (result[i] == '(' || result[i] == ')'){
            result.erase(i, 1);
            i--;
        }
        
    }
               
    //std::cout << "teste " << result <<  "\n";
}

/**
 * @brief Checks if the char is a digit
 * @param digit char variable to be checked if its a digit
*/
bool Pos_fixed::is_number(char digit){
    return std::isdigit(static_cast<unsigned char>(digit)) != 0;
}

/**
 * @brief Checks if the string is convertible to int
 * @param str string to be checked if can be converted to int
*/
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

/**
 * @brief Returns the result string variable
 * @return result expression posfixed
*/
std::string Pos_fixed::return_result(){
    return result;
}

/**
 * @brief Resets the class
*/
void Pos_fixed::clear(){
    m_exp.clear();
    result.clear();
    while(!m_ope.empty()){
        m_ope.pop();
    }
    while(!m_number.empty()){
        m_number.pop();
    }
}