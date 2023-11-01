#include <iostream>
#include "tokenizer.h"
#include <string>
using namespace std;    

int main() {

    Tokenizer tk_raw_line, tk_no_spaces, tk_single_char;

    Tokenizer temp; // Auxiliar Tokenizer to pass tokenizer lists from one to another
    
    std::string line; // Line that will be read
    std::getline(std::cin >> std::ws, line);    // Reading line ignoring white spaces

    tk_raw_line.tokens(line, " \t", true);   // Tokenize Line with " \t", 
    // This tokenize the tokens but it's still needed to remove some undesired tokens

    // With the method above there will be empty tokens "()", sometimes a token with spaces " " at the start like this for example: "(  123)" 
    // and sometimes tokens only with spaces. The latter are \t that will show up like this "(    )"

    // Remove the "()" tokens and pass them to tk_no_spaces
    for (int i = 0; i < tk_raw_line.size(); i++){
        
        // Use for testing
        //std::cout << "("<< tk.get_token() << ")";
        
        if (tk_raw_line.get_token() != ""){
            tk_no_spaces.set_tokens(tk_raw_line.get_token());
        }
        tk_raw_line.next();
    } std::cout << std::endl;
    
    std::string token;  // Current token


    // This loop completely removes spaces from the tokens, so all tokens are carachters held together without spaces in between. 
    // i.e: there arent tokens like this: "(str 2)", as they will be split into:
    // "(str", "2)" 
    std::cout << "No spaces: " << std::endl;
            for (int i = 0; i < tk_no_spaces.size(); i++){
                
                token = tk_no_spaces.get_token(); // Current token from tk_no_spaces
                
                // This is an undesired token that sometimes appear
                // We dont want it to go further
                if (token == "\t"){
                    // Use for testing
                    //std::cout << "hey";
                } 
                
                else {

                    // Remove white spaces before the first digit that is not a whitespace:
                    size_t startPos = token.find_first_not_of('\t');
                    if (startPos != std::string::npos) {
                        // Erase the leading spaces
                        token.erase(0, startPos);
                    }
            
                    std::cout << "(" << token << ")";
                    temp.set_tokens(token);
                }
                tk_no_spaces.next();
            } std::cout << std::endl;

            tk_no_spaces.reset();
            for(int i = 0; i < temp.size(); i++){
                tk_no_spaces.set_tokens(temp.get_token());
                temp.next();
            }

    // So, after the previous loops it's still necessary to separate the tokens into single charachters and positive numbers, then after it fix the negative integer values
    
    tk_no_spaces.seek(0);
    for (int i = 0; i < tk_no_spaces.size(); i++){
        token = tk_no_spaces.get_token();
        
        if (token.size() == 1){
            tk_single_char.set_tokens(token);
        } else if (token.size() != 1) {
            for (int j = 0; j < token.size(); j++){
                
                if (token[j] == '(') {
                    tk_single_char.set_tokens("(");
                } else if (token[j] == ')'){
                    tk_single_char.set_tokens(")");
                } else if (token[j] == '+'){
                    tk_single_char.set_tokens("+");
                } else if (token[j] == '-'){
                    tk_single_char.set_tokens("-");
                } else if (token[j] == '/'){
                    tk_single_char.set_tokens("/");
                } else if (token[j] == '*'){
                    tk_single_char.set_tokens("*");
                } else if (token[j] == '%'){
                    tk_single_char.set_tokens("%");
                } else if (token[j] == '^'){
                    tk_single_char.set_tokens("^");
                } 
                
                // token[j] não é um parenteses ou operadores, então tem que ser número
                else {
                    std::string pos_num;
                    pos_num = token[j];
                    while(token[j + 1] == '0' || token[j + 1] == '1' || token[j + 1] == '2' || token[j + 1] == '3' || token[j + 1] == '4' || token[j + 1] == '5' || token[j + 1] == '6' || token[j + 1] == '7' || token[j + 1] == '8' || token[j + 1] == '9'){
                        pos_num += token[j + 1];
                        j++;
                    }
                    tk_single_char.set_tokens(pos_num);
                    pos_num.clear();
                }
                
            }
        }
        tk_no_spaces.next();
    }

    tk_single_char.seek(0);
    std::cout << "Single charachters and positive numbers: " << std::endl;
    for (int i = 0; i < tk_single_char.size();i++){
        token = tk_single_char.get_token();
        std::cout << "( " << tk_single_char.get_token() << " ) ";
        tk_single_char.next();
    } std::cout << std::endl;
    

    // Now we fix the negative integer values

    for (int i = 0; i < tk_single_char.size();i++){

    }


    std::cout << std::endl;
    return 0;
}