#include <iostream>
#include "tokenizer.h"
#include <string>
using namespace std;    

int main() {

    Tokenizer tk_raw_line, tk_no_spaces, tk_single_char, tk_final;

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
    // i.e: there arent tokens like this: "(-num 2)", as they will be split into:
    // "(-num", "2)" 
    // std::cout << "No spaces: " << std::endl;
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
    
            //std::cout << "(" << token << ")";
            temp.set_tokens(token);
        }
        tk_no_spaces.next();
    } std::cout << std::endl;

    tk_no_spaces.reset();
    for(int i = 0; i < temp.size(); i++){
        tk_no_spaces.set_tokens(temp.get_token());
        temp.next();
    }

    // So, after the previous loops it's still necessary to separate the tokens into single charachters and positive numbers, then after this next loop fix the negative integer values
    // This next loop makes tokens like this: "(-num", "2)" . Into this: "(", "-", "num", "2", ")"
    
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
    /*std::cout << "Single charachters and positive numbers: " << std::endl;
    for (int i = 0; i < tk_single_char.size();i++){
        token = tk_single_char.get_token();
        std::cout << tk_single_char.get_token() << " ";
        tk_single_char.next();
    } std::cout << std::endl;*/
    
    // Now we fix the negative integer values
    tk_single_char.seek(0);

    // Auxiliar bool types
    bool prev_is_number{false}; // Prev token is a number
    bool prev_is_closing{false};    // Prev token is ")". This is important because after it its always expected for "-" to be a subtraction
    bool prev_is_operator{false};   // Prev token its a operator that accepts - as a negative value after it. EX: /, *, %, +. Not prev operator: ).
                                    // (After ")" its ALWAYS expected for "-"" to be a subtraction and not an negative value)

    int zero{0};
    for (int i = 0; i < tk_single_char.size();i++){
        
        token = tk_single_char.get_token();
        std::cout << i << " " << token << std::endl;
        if(token == "("){
            tk_final.set_tokens(token);

            prev_is_operator = true;    // For next token indicate that previous token is operator
            prev_is_closing = false;
            prev_is_number = false;

        } else if (token == ")") {
            tk_final.set_tokens(token);

            prev_is_closing = true;     // For next token indicate that previous token is ")"
            prev_is_number = false;
            prev_is_operator = false;

        } else if (token == "+") {
            tk_final.set_tokens(token);

            prev_is_operator = true;    // For next token indicate that previous token is operator
            prev_is_closing = false;
            prev_is_number = false;

        } else if (token == "/") {
            tk_final.set_tokens(token);

            prev_is_operator = true;    // For next token indicate that previous token is operator
            prev_is_closing = false;
            prev_is_number = false;

        } else if (token == "*") {
            tk_final.set_tokens(token);

            prev_is_operator = true;    // For next token indicate that previous token is operator
            prev_is_closing = false;
            prev_is_number = false;

        } else if (token == "%") {
            tk_final.set_tokens(token);

            prev_is_operator = true;    // For next token indicate that previous token is operator
            prev_is_closing = false;
            prev_is_number = false;

        } else if (token == "^") {
            tk_final.set_tokens(token);

            prev_is_operator = true;    // For next token indicate that previous token is operator
            prev_is_closing = false;
            prev_is_number = false;

        } 
        
        // Else if the current token is a positive number alone (the "-" cases were already dealt with) tokenize them as they are
        else if (token[0] == '0' || token[0] == '1' || token[0] == '2' || token[0] == '3' || token[0] == '4' || token[0] == '5' || token[0] == '6' || token[0] == '7' || token[0] == '8' || token[0] == '9'){
            tk_final.set_tokens(token);

            prev_is_number = true;  // For next token indicate that previous token is number
            prev_is_closing = false;
            prev_is_operator = false;
        }
        
        else if (token == "-" ){
            // If token == "-", there are a few cases to note: 
            
            std::string token_aux;  // Auxiliar next token

            // Else, tokenize the "-" alone
            if (i == (tk_single_char.size() - 1 )){
                tk_final.set_tokens(token);

                prev_is_operator = true;    // For next token indicate that previous token is operator
                prev_is_number = false;
                prev_is_closing = false;
            } 
            
            else {
                
                // Get next token and return back to previous token position
                tk_single_char.next();          
                token_aux = tk_single_char.get_token();
                tk_single_char.prev();
                
                std::cout << " oi ";
                
                // If the token "-" is the first token, and after it it's a number, than concatonate both and set a token, for it's an integer value
                if(i == 0 && (token_aux[zero] == '0' || token_aux[zero] == '1' || token_aux[zero] == '2' || token_aux[zero] == '3' || token_aux[zero] == '4' || token_aux[zero] == '5' || token_aux[zero] == '6' || token_aux[zero] == '7' || token_aux[zero] == '8' || token_aux[zero] == '9')){
                    token += token_aux; 
                    tk_final.set_tokens(token);
                    tk_single_char.next(); // we tokenized the number with "-"
                    i++;

                    prev_is_number = true;  // For next token indicate that previous token is number
                    prev_is_closing = false;
                    prev_is_operator = false;
                } 
                // If the token "-" is the first token, and after it it's not a number, than set the token as only "-"
                else if (i == 0 && (token_aux[zero] != '0' && token_aux[zero] != '1' && token_aux[zero] != '2' && token_aux[zero] != '3' && token_aux[zero] != '4' && token_aux[zero] != '5' && token_aux[zero] != '6' && token_aux[zero] != '7' && token_aux[zero] != '8' && token_aux[zero] != '9')){
                    tk_final.set_tokens(token);

                    prev_is_operator = true;    // For next token indicate that previous token is operator
                    prev_is_number = false;
                    prev_is_closing = false;
                }

                // If the token "-" is not in the first position and the next token is not a number, then the current "-" is always expected to be alone
                // and be a subtraction
                // Its important for this to be checked first.
                else if (i != 0 && (token_aux[zero] != '0' && token_aux[zero] != '1' && token_aux[zero] != '2' && token_aux[zero] != '3' && token_aux[zero] != '4' && token_aux[zero] != '5' && token_aux[zero] != '6' && token_aux[zero] != '7' && token_aux[zero] != '8' && token_aux[zero] != '9')){
                    tk_final.set_tokens(token);
                    std::cout << token_aux;
                    std::cout << " 5 passou aqui" << std::endl;
                    prev_is_operator = true;    // For next token indicate that previous token is operator
                    prev_is_number = false;
                    prev_is_closing = false;
                }

                // If the token "-" is not in the first position and the previous token is an operator ( operators in this case exclude ")" ), that means that this "-"" is expecting a positive number after it.
                // As it will become a negative value. If it doesnt find a number, tokenize it alone and it will be notified in the parsing
                // If it does find a number, then tokenize them together
                else if (i != 0 && (prev_is_operator == true) ){

                    // If next token is not a number, tokenize the "-" alone
                    if (token_aux[zero] != '0' && token_aux[zero] != '1' && token_aux[zero] != '2' && token_aux[zero] != '3' && token_aux[zero] != '4' && token_aux[zero] != '5' && token_aux[zero] != '6' && token_aux[zero] != '7' && token_aux[zero] != '8' && token_aux[zero] != '9'){
                        
                        tk_final.set_tokens(token);

                        prev_is_operator = true;    // For next token indicate that previous token is operator
                        prev_is_number = false;
                        prev_is_closing = false;
                    } 
                    
                    // If next token IS a number, tokenize them both togeter
                    else if (token_aux[zero] == '0' || token_aux[zero] == '1' || token_aux[zero] == '2' || token_aux[zero] == '3' || token_aux[zero] == '4' || token_aux[zero] == '5' || token_aux[zero] == '6' || token_aux[zero] == '7' || token_aux[zero] == '8' || token_aux[zero] == '9'){
                        token += token_aux; 
                        tk_final.set_tokens(token);
                        std::cout << " oi ";
                        tk_single_char.next(); // we tokenized the number with "-"
                        i++;
                        std::cout << " oi ";
                        prev_is_number = true;  // For next token indicate that previous token is number
                        prev_is_closing = false;
                        prev_is_operator = false;
                    }
                } 

                // If the token "-"" is not in the first position and the previous token is a number, than this "-" token is always expected to be alone as a subtraction
                else if (i != 0 && (prev_is_number == true)){
                    tk_final.set_tokens(token);

                    prev_is_operator = true;    // For next token indicate that previous token is operator
                    prev_is_number = false;
                    prev_is_closing = false;
                }

                // If the token "-"" is not in the first position and the previous token is ")" , than this "-" token is always expected to be alone as a subtraction
                else if (i != 0 && (prev_is_closing == true)){
                    tk_final.set_tokens(token);

                    prev_is_operator = true;    // For next token indicate that previous token is operator
                    prev_is_number = false;
                    prev_is_closing = false;
                }
            }
        }

        // Else if the current token is a positive number alone (the "-" cases were already dealt with) tokenize them as they are
        else if (token[0] == '0' || token[0] == '1' || token[0] == '2' || token[0] == '3' || token[0] == '4' || token[0] == '5' || token[0] == '6' || token[0] == '7' || token[0] == '8' || token[0] == '9'){
            tk_final.set_tokens(token);

            prev_is_number = true;  // For next token indicate that previous token is number
            prev_is_closing = false;
            prev_is_operator = false;
        }
        tk_single_char.next();
    }

    std::cout << std::endl << "Tokens finais: " << std::endl;

    for (int i = 0; i < tk_final.size(); i++){
        token = tk_final.get_token();
        std::cout << token << " ";
        tk_final.next();
    }

    std::cout << std::endl;
    return 0;
}