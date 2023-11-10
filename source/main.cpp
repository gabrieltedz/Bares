#include <iostream>
#include "Parsing.h"
#include "pos_fixed.h"
#include "Calculator.h"
#include <string>
using namespace std;    

int main() {

    Parser parser;
    std::string expression_infixed;
    std::string line; // Line that will be read
    while(std::getline(std::cin, line)){
        parser.clear();
        parser.receive_line(line);
        parser.to_raw_line();
        parser.to_no_spaces();
        parser.to_single_char();
        parser.to_final();

        if (parser.invalid == false){
            expression_infixed = parser.get_expression_codified();
            Pos_fixed m_pos_fix{expression_infixed};
            m_pos_fix.pos(expression_infixed);

            Calculator calc;
            calc.receive_expression(m_pos_fix.return_result() , line);
            int result = calc.calculate();
            std::cout << result << std::endl;


            calc.clear();
            m_pos_fix.clear();
        } else {

        }
        
    }


    
    return 0;
}