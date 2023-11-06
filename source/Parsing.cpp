#include <iostream>
#include <string>
#include "Parsing.h"

void Parser::receive_line(std::string str){
    line = str;
}

bool Parser::isConvertibleToInt(std::string str){
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

void Parser::to_raw_line(){
    tk_raw_line.tokens(line, " \t", true);   // Tokenize Line with " \t", 
    tk_raw_line.seek(0);
    // This tokenize the tokens but it's still needed to remove some undesired tokens

    // With the method above there will be empty tokens "()", sometimes a token with spaces " " at the start like this for example: "(  123)" 
    // and sometimes tokens only with spaces. The latter are \t that will show up like this "(    )"
}

void Parser::to_no_spaces(){
    // Remove the "()" tokens and pass them to tk_no_spaces
    for (int i = 0; i < tk_raw_line.size(); i++){
        
        // Use for testing
        //std::cout << "("<< tk.get_token() << ")";
        
        if (tk_raw_line.get_token() != ""){
            tk_no_spaces.set_tokens(tk_raw_line.get_token());
        }
        tk_raw_line.next();
    }
    tk_raw_line.seek(0);

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

    // Repass the desired tokens in this step to tk_no_spaces
    tk_no_spaces.reset();
    for(int i = 0; i < temp.size(); i++){
        tk_no_spaces.set_tokens(temp.get_token());
        temp.next();
    }
    tk_no_spaces.seek(0);
}

void Parser::to_single_char(){

    // So, after the previous loops it's still necessary to separate the tokens into single charachters and positive numbers, then after this next loop fix the negative integer values
    // This next loop makes tokens like this: "(-num", "2)" . Into this: "(", "-", "num", "2", ")"
    std::string token;
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

    // After the previous loop there are still tokens with letters and other symbols undesired, however,
    // The next loop filters them out

    tk_single_char.seek(0);

}

void Parser::to_final(){
    // Now we fix the negative integer values and also filter letters
    tk_single_char.seek(0);

    std::string token;
    // Auxiliar bool types
    bool prev_is_number{false}; // Prev token is a number
    bool prev_is_closing{false};    // Prev token is ")". This is important because after it its always expected for "-" to be a subtraction
    bool prev_is_operator{false};   // Prev token its a operator that accepts - as a negative value after it. EX: /, *, %, +. Not prev operator: ).
                                    // (After ")" its ALWAYS expected for "-"" to be a subtraction and not an negative value)

    int zero{0};
    for (int i = 0; i < tk_single_char.size();i++){
        
        token = tk_single_char.get_token();
        
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
                        
                        tk_single_char.next(); // we tokenized the number with "-"
                        i++;
                        
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
    tk_final.seek(0);
    std::cout << std::endl;

    int parent_counter{0};
    bool is_expected_number_or_op_parent{true}; // (1)
    bool is_expected_operator{false};           // (2)
    bool can_be_expected_end_parent{false};     // (3)
    bool invalid{false};

    std::string aux_token;
    int v_aux_token;

    for (int i = 0; i < tk_final.size(); i++){
        token = tk_final.get_token();
        
        // For the first position is always expected "(" or a number, else is invalid
        if (i == 0){
            if (token == "("){
                parent_counter++;
                can_be_expected_end_parent = true;
                is_expected_number_or_op_parent = true;
                is_expected_operator = false;
            } else if (isConvertibleToInt(token) == true){
                is_expected_operator = true;
                is_expected_number_or_op_parent = false;
            } else {
                //error
                std::cout << "not number or ( at first token";
                invalid = true;
                break;
            }
        }

        // For not the first position but not the last position
        else if (i != 0 && i != (tk_final.size() - 1) ) {
            // If its expected an operator (always after number or ")" ) and the token it's not an operator, its an error
            if (is_expected_operator == true){
                if (token == "+" || token == "-" || token == "%" || token == "/" || token == "*" || token == "^"){
                    // If the token is an operator, then it's expected "(" or a number
                    is_expected_number_or_op_parent = true;
                    is_expected_operator = false;
                } else if (token == ")"){
                    if (can_be_expected_end_parent == true){
                        parent_counter--;
                        if (parent_counter == 0){
                            can_be_expected_end_parent = false;
                        }
                    } else if (can_be_expected_end_parent == true) {
                        //error
                        std::cout << "this is an invalid end parenthesis" << "!";
                        invalid = true;
                        break;
                    } else {

                    }
                    
                } else {
                    //error
                    std::cout <<"expected operator after token" << i << "!";
                    invalid = true;
                    break;
                }
            }
            // If it's expected a number or "(", if its not that then it's error;
            else if (is_expected_number_or_op_parent == true) {
                if (token == "("){
                    parent_counter++;
                    can_be_expected_end_parent = true;
                    // Dont change anything, as after "(" it's still expected "(" or a number
                } 
                
                // If its a number, then after it it's expected an operator
                else if (isConvertibleToInt(token) == true){
                    is_expected_number_or_op_parent = false;
                    is_expected_operator = true;
                } else {
                    invalid = true;
                    std::cout << "expected number after token" << i << "!";;
                    break;
                }
            }
        }

        // At the last token, if there wasnt any erros in the middle of the equation, then its expected to end on a number or ")"
        // Also, its not supposed to wait for more ")" after it (if the last ")" is the last token then its ok)
        else if (i == (tk_final.size() - 1) ){
            
            // If its not expecting end parent, then it can only end with a number
            if (can_be_expected_end_parent == false){
                //std::cout << "oi" << std::endl;
                //
                if (is_expected_number_or_op_parent == true){
                    if (isConvertibleToInt(token) == true){
                    // Its valid
                    } else if (token == "+" || token == "-" || token == "%" || token == "/" || token == "*" || token == "^"){
                        invalid = true;
                        std::cout << "expected number but it was operator " << token << "!";;
                        break;
                    } else if (token == "(" || token == ")"){
                        invalid = true;
                        std::cout << "expected number but it was " << token << "!";;
                        break;
                    }
                } 
                // Error
                else {
                    // Error
                    invalid = true;
                    if (token == "(" || token == ")"){
                        std::cout << "Unpaired " << token << " at the end" << std::endl;
                    } 
                    
                    else if (token == "+" || token == "-" || token == "/" || token == "*" || token == "%" || token == "^"){
                        std::cout << "extra " << token << " at the end" << std::endl;
                    } 

                    else if (isConvertibleToInt(token) == true){
                        std::cout << "missing operator before last number!" << std::endl;
                    }
                    else {
                        std::cout << "testing" << std::endl;
                    }
                    
                    break;
                    
                    
                }
                
                   /*else if (is_expected_number_or_op_parent == false){
                    if (token[0] == '0' || token[0] == '1' || token[0] == '2' || token[0] == '3' || token[0] == '4' || token[0] == '5' || token[0] == '6' || token[0] == '7' || token[0] == '8' || token[0] == '9'){
                    // Its NOT valid
                    }
                }
                // First check for number, if its a number than its valid, as long as its not expecting any end parentesis
                 else if (token[0] == '-' || token[0] == '+' || token[0] == '*' || token[0] == '%' || token[0] == '/' || token[0] == '^'){
                    std::cout << "Extra operator " << token << "at the end" << std::endl;

                } else if (token[0] == ')'){
                    std::cout << "extra ')' unpaired at the end" << std::endl;
                } else {
                    std::cout << "this error" << std::endl;
                }*/
            } 
            // If it's still experecting an end parent, then the only way it will pass through here is if the token is an end parenthesis,
            // As it is the last token. Else, its an error.
            // Also, it must be the last end parenthesis, if it's still expecting one after the last one, then it's an error 
            else if (can_be_expected_end_parent == true){
                if (token == ")"){
                    if (parent_counter == 1){
                        // Its valid
                    } else if (parent_counter > 1){
                        std::cout << "its missing closing parentesis" << std::endl;
                    } else {
                        //There is no other case for this
                    }
                } 
                // If token it's not an end parenthesis, its an error
                else {
                    invalid = true;
                    std::cout << "I'm expected a missing closed parenthesis!" << std::endl;
                    break;
                }
                
            }
            
            

            // Check if it's still expected one last end parentesis
            else if (can_be_expected_end_parent == true){
                if (token == ")" && parent_counter == 1){
                    //its valid
                } 
                // Else if token == ")" but parent counter > 1
                else if (token == ")" && parent_counter > 1){
                    // Error
                    invalid = true;
                    std::cout << "it's missing the end parenthesis!";
                    break;
                }
                // Or token != ")";
                else if (token != ")"){
                    // error
                    invalid = true;
                    std::cout << "it's missing an end parenthesis!";
                    break;
                }
            } 

            else {
                // erro
                invalid = true;
                std::cout << "what case was this";
                break;
            }
        }
        tk_final.next();
    }
   
    if (!invalid){
        std::cout << "valid" << std::endl;
    } else {
        std::cout << "invalid" << std::endl;
    }
}

