#include <iostream>
#include "Parsing.h"
#include "pos_fixed.h"
#include <string>
using namespace std;    

int main() {

    Parser parser;

    std::string line; // Line that will be read
    std::getline(std::cin, line);    // Reading line

    std::cout << line << std::endl;
    
    parser.receive_line(line);
    parser.to_raw_line();
    parser.to_no_spaces();
    parser.to_single_char();
    parser.to_final();

    std::string expression_infixed = parser.get_expression_codified();

    std:: cout << "aqui está a expressão: " << expression_infixed << std::endl;

    Pos_fixed A{expression_infixed};
    A.pos(expression_infixed);
    
    return 0;
}