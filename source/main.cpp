#include <iostream>
#include "Parsing.h"
#include "pos_fixed.h"
#include "Calculator.h"
#include <string>
using namespace std;    

int main() {

    Parser parser; // Declaration of parser object from Parser class
    std::string expression_infixed; // Infixed expression
    std::string line; // Line that will be read

    // Keep reading lines until there are none left
    while(std::getline(std::cin, line)){

        // Clear the parser
        parser.clear();

        //receive line
        parser.receive_line(line);

        // Do the conversion to the tokens
        parser.to_raw_line();
        parser.to_no_spaces();
        parser.to_single_char();
        // This is the most important one
        parser.to_final();

        // After previous conversions, if invalid = true it outputs it's respective error message
        // Else if invalid = false, that means the expression is (supposed) to be valid and is sent to the infix to posfix program

        if (parser.invalid == false){
            expression_infixed = parser.get_expression_codified();
            Pos_fixed m_pos_fix{expression_infixed};
            m_pos_fix.pos(expression_infixed);

            Calculator calc;
            calc.receive_expression(m_pos_fix.return_result() , line);
            int result = calc.calculate();
            if (calc.out_of_range == true){
                
            } else if (calc.div_by_zero == true){
            
            } else if (calc.num_overflow == true){

            } else if (calc.und_value == true){

            }   else {
                std::cout << result << std::endl; 
            }
            


            calc.clear();
            m_pos_fix.clear();
        } else {

        }
        
    }


    
    return 0;
}
