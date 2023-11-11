#ifndef _PARSING_TOKEN_
#define _PARSING_TOKEN_

#include <string>
#include <iostream>
#include "tokenizer.h"

/**
 * @brief Parsing and tokenizing class
*/
class Parser {
private:
    // Tokenizers, also used as "buffers" for the tokens they carry
    Tokenizer tk_raw_line, tk_no_spaces, tk_single_char, tk_final;

    Tokenizer temp; // Auxiliar Tokenizer to pass tokenizer lists from one to another
    std::string line; // Line read

public:
    /**
     * @brief bool value to indicate if the the expression is invalid for some reason
     * if so, it doesnt go further and sends the error message!
    */
    bool invalid{false};

    /**
     * @brief Constructor
    */
    Parser() = default;

    /**
     * @brief Deconstructor
    */
    ~Parser() = default;

    /**
     * @brief Transform line into raw tokens
    */
    void to_raw_line(); 

    /**
     * @brief Take out undesired spaces
    */
    void to_no_spaces();  

    /**
     * @brief reduce to 1 character tokens and numbers
    */
    void to_single_char();  

    /**
     * @brief Reconstruct the line with integer values and discard tokens with letters
    */
    void to_final();        // Reconstruct the line with integer values and discard tokens with letters

    /**
     * @brief Receive original line
     * @param str original string line expression
    */
    void receive_line(std::string str);

    /**
     * @brief checks if the string is convertible to string
    */
    bool isConvertibleToInt(std::string str);

//============================================================

    // Auxiliary functions to encounter errors

    int find_operator_without_number();
    int first_term_missing();
    int find_first_parenthesis_without_number();
    int find_missing_operator_after_number();
    int find_missing_operator_after_end_parenthesis();
    int find_mistake_end_or_opening_parenthesis();
    
//============================================================
    
    /**
     * @brief Return the valid infixed expression codified with '@' to indicate int values after it
    */
    std::string get_expression_codified();

    /**
     * @brief Resets the class
    */
    void clear();
};

/**
 * @brief Class of error types
*/
enum class ErrorType {
    First_Term_Missing = 0,
    Missing_Number,
    Missing_Number_After_Parenthesis,
    Missing_Close_Parent,
    Missing_Operand,
    Missing_Operand_After_End_Parenthesis,
    Mistake_Parenthesis
};

#endif 