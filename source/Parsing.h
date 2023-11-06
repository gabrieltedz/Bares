#ifndef _PARSING_TOKEN_
#define _PARSING_TOKEN_

#include <string>
#include <iostream>
#include "tokenizer.h"

class Parser {
private:
    // Tokenizers, also used as "buffers" for the tokens they carry
    Tokenizer tk_raw_line, tk_no_spaces, tk_single_char, tk_final;

    Tokenizer temp; // Auxiliar Tokenizer to pass tokenizer lists from one to another
    std::string line; // Line read

public:
    Parser() = default;
    ~Parser() = default;

    void to_raw_line(); // Transform line into raw tokens
    void to_no_spaces();    // Take out undesired spaces
    void to_single_char();  // Reduce to 1 charachter tokens and numbers
    void to_final();        // Reconstruct the line with integer values and discard tokens with letters

    void receive_line(std::string str);

    bool isConvertibleToInt(std::string str);

};

#endif 