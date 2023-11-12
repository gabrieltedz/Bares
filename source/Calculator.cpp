#include "Calculator.h"

int Calculator::isConvertibleToInt(std::string str){
    int number;
    number = std::stoi(str);
    if (number >= -32768 && number <= 32767){
        return 0;
    } 
    return 1;       
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
    int n_out_of_range;
     std::string check_result;
    std::string int_numbr;
    for (int i = 0; i < expression.size(); i++){
        // If you find a '@', that means there's a int number ahead
        if (expression[i] == '@'){
            i++;
            
            int_numbr = expression[i];
            i++;
            while(true){
                if (is_number(expression[i])){
                    int_numbr += expression[i];
                    if (isConvertibleToInt(int_numbr) == 1){
                        n_out_of_range = stoi(int_numbr);
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
            if(out_of_range == true){
                break;
            }
        } else if (expression[i] == '+'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            result = (op1 + op2);

            check_result = std::to_string(result);
            if(isConvertibleToInt(check_result) == 1){
                num_overflow = true;
                break;
                //numeric overflow error!!
            }
            
            m_stack.push(result);
        } else if (expression[i] == '-'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            result = (op1 - op2);

            check_result = std::to_string(result);
            if(isConvertibleToInt(check_result) == 1){
                num_overflow = true;
                break;
                //numeric overflow error!!
            }
            
            m_stack.push(result);
        } else if (expression[i] == '*'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            result = (op1 * op2);

            check_result = std::to_string(result);
            if(isConvertibleToInt(check_result) == 1){
                num_overflow = true;
                break;
                //numeric overflow error!!
            }
            
            m_stack.push(result);
        } else if (expression[i] == '^'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            if (op1 == 0 && op2 == 0){
                // Undefined value!!
                und_value = true;
                std::cout << "Undefined value!" << std::endl;
            }
            double value = power(op1,op2);
        
            result = value;

            check_result = std::to_string(result);
            if(isConvertibleToInt(check_result) == 1){
                num_overflow = true;
                break;
                //numeric overflow error!!
            }
            
            m_stack.push(result);
        } else if (expression[i] == '/'){
            op2 = m_stack.top();
            if (op2 == 0){
                // Erro aqui
                div_by_zero = true;
                break;
            } else {
                m_stack.pop();
                op1 = m_stack.top();
                m_stack.pop();
                result = (op1 / op2);
                check_result = std::to_string(result);
            if(isConvertibleToInt(check_result) == 1){
                num_overflow = true;
                break;
                //numeric overflow error!!
            }
                m_stack.push(result);
            }
            
        } else if (expression[i] == '%'){
            op2 = m_stack.top();
            m_stack.pop();
            op1 = m_stack.top();
            m_stack.pop();

            result = (op1 % op2);
            check_result = std::to_string(result);
            if(isConvertibleToInt(check_result) == 1){
                num_overflow = true;
                break;
                //numeric overflow error!!
            }
            
            m_stack.push(result);
        }
    }
    
    if (out_of_range == true){
        //use find para achar o termo fora
        std::cout << "Integer constant out of range beginning at column (" << original_line.find(int_numbr) + 1 << ")!" << std::endl;
        return 0;
    } else if (div_by_zero == true) {
        std::cout << "Division by zero!" << std::endl;
        return 0;
    } else if (num_overflow == true){
        std::cout << "Numeric overflow error!" << std::endl;
        return 0;
    }
    
    else {
        result = m_stack.top();
        return result;
    }
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
    out_of_range = false;
    div_by_zero = false;
    und_value = false;
    num_overflow = false;
}
