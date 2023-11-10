#include "Calculator.h"

int Calculator::isConvertibleToInt(std::string str){
    try {
            std::stoi(str);
            return 0;
        } catch (const std::out_of_range& e) {
            // The string is convertible to an integer, but it's out of the valid range for int.
            return 1;
        }
}

double power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

bool Calculator::is_number(char digit){
    return std::isdigit(static_cast<unsigned char>(digit)) != 0;
}

void Calculator::receive_expression(std::string expr, std::string orig_line){
    expression = expr;
    original_line = orig_line;
}

int Calculator::calculate(){
    // Iterate through out the expression
    bool out_of_range{false};
    for (int i = 0; i < expression.size(); i++){
        // If you find a '@', that means there's a int number ahead
        if (expression[i] == '@'){
            i++;
            std::string int_numbr;
            int_numbr = expression[i];
            i++;
            while(true){
                if (is_number(expression[i])){
                    int_numbr += expression[i];
                    if (isConvertibleToInt(int_numbr) == 1){
                        out_of_range = true;
                        break;
                        //Integer constant out of range begginng at column...
                    }

                } else {
                    int value;
                    value = stoi(int_numbr);
                    m_stack.push(value);
                    i--;
                    break;
                }
                i++;
            }
        } else if (expression[i] == '+'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            result = (op1 + op2);
            
            m_stack.push(result);
        } else if (expression[i] == '-'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            result = (op1 - op2);
            
            m_stack.push(result);
        } else if (expression[i] == '*'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            if (op1 == 0 || op2 == 0){
                // Multiplication by zero!!
            }

            result = (op1 * op2);
            
            m_stack.push(result);
        } else if (expression[i] == '^'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            if (op1 == 0 && op2 == 0){
                // Undefined value!!
                std::cout << "passou aqui!";
            }
            double value = power(op1,op2);
            if (value){
                //if value out of range...
            }
            result = value;
            
            m_stack.push(result);
        } else if (expression[i] == '/'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            if (op2 == 0){
                // Division by zero!!
                std::cout << "divisão por zero?";
            }

            result = (op1 / op2);
            
            m_stack.push(result);
        } else if (expression[i] == '%'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            result = (op1 % op2);
            
            m_stack.push(result);
        }
        std::string check_result = std::to_string(result);
        if(isConvertibleToInt(check_result) == 1){
            out_of_range = true;
            //numeric overflow error!!
        }
    }
    
    if (out_of_range == true){
        //use find para achar o termo fora
    }
    result = m_stack.top();
    //std::cout << "Here is the result of the expression: " << result << std::endl;
    return result;
}

void Calculator::clear(){
    expression.clear();
    original_line.clear();
    op1 = {0};
    op2 = {0};
    result = {0};
    while (!m_stack.empty()) {
        m_stack.pop();
    }
}