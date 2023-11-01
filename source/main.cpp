#include <iostream>
#include "tokenizer.h"
using namespace std;    

int main() {

    Tokenizer tk_raw_line, tk_no_spaces, tk3;
    
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
        }
        tk_no_spaces.next();
    }

    // So, after the previous loop it's still necessary

    for (int i = 0; i < )


    std::cout << std::endl;
    return 0;
}