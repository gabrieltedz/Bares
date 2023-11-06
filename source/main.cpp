#include <iostream>
#include "Parsing.h"
#include <string>
using namespace std;    

int main() {

    Parser parser;

    std::string line; // Line that will be read
    std::getline(std::cin >> std::ws, line);    // Reading line ignoring white spaces
    
    parser.receive_line(line);
    parser.to_raw_line();
    parser.to_no_spaces();
    parser.to_single_char();
    parser.to_final();
    
    return 0;
}