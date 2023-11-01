#include <iostream>
#include "tokenizer.h"
using namespace std;    

int main() {

    

    Tokenizer tk, tk2, tk3;
    std::string token;
    std::string line;
    std::getline(std::cin >> std::ws, line);

    tk.tokens(line, " \t", true);

    for (int i = 0; i < tk.size(); i++){
        if (tk.get_token() != ""){
            tk2.set_tokens(tk.get_token());
        }
        tk.next();
    }
    tk.seek(0);

    for (int i = 0; i < tk2.size(); i++){
      
        token = tk2.get_token();
        if (token == "\t"){
            std::cout << "hey";

        } else if ( token == " ") {
            std::cout << "hey2";
        } else if (token == ""){
            std::cout << "hey3";
        }
        
        else {
            /*std::string str = tk.get_token();
            std::vector<char> str2;
            for (int j = 0; j < str.size(); j++){
                if (str[j] == ' '){

                } else {
                    str2.push_back(str[j]);
                }
            }
            std::string str3(str2.begin(), str2.end());*/

             size_t startPos = token.find_first_not_of('\t');

                if (startPos != std::string::npos) {
                    // Erase the leading spaces
                    token.erase(0, startPos);
                }
    
            std::cout << "(" << token << ")";
        }


        tk2.next();
    }


    std::cout << std::endl;
    return 0;
}