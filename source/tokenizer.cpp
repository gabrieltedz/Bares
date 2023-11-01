#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "tokenizer.h"
using namespace std;


/**
 * @brief This function performs the tokenization of a string. 
 * 
 * (código de gabriel, mexer apenas se necessário)
 *
 * @param m_input The string to be tokenized.
 * @param m_delimit The set of characters acting as delimiters to separate words.
 * @param m_trim Indicates whether leading and trailing spaces of words should be removed.
 */
void Tokenizer::tokens(string m_input, string m_delimit, bool m_trim) {

  /// Remove leading and trailing spaces if m_trim is true
  if (m_trim) {
    size_t start = m_input.find_first_not_of(" \t");
    size_t end = m_input.find_last_not_of(" \t");
    if (start != std::string::npos && end != std::string::npos) {
      m_input = m_input.substr(start, end - start + 1);
    } 
    else {
      /// The string is empty or contains only whitespace, nothing to tokenize
    }
  }

  /// Reset control variables
  begin = 0;
  endd = 0;

  /// While not traversing the entire string
  while (endd < m_input.size()) {
    // Pos is an element of the string
    auto pos = m_delimit.find(m_input[endd]);

    /// Split the word into a token using a specific delimiter character, with or without spaces
    if (pos != string::npos) {
      token = m_input.substr(begin, endd - begin);
      set_tokens(token);

      begin = endd + 1;
      endd = begin;
    }
    endd++;
  }

  /// Check if any word is missing
  if (begin < m_input.size()) {
    token = m_input.substr(begin);
    set_tokens(token);
  }

  // Remove spaces from tokens if necessary
  if (m_trim) {
    for (size_t i = 0; i < m_tokens.size(); i++) {
      token.clear();
      size_t j = 0;

      while (j < m_tokens[i].length()) {
        if (m_tokens[i][j] != ' ') {
          token += m_tokens[i][j];
        }
        j++;
      }

      std::string token2 = "";
      for (char c : token) {
        if (c != ' ' && c != '\0') {
          token2 += c;
        }
      }

      m_tokens[i] = token2;
    }
  }

  
}

/**
 * @brief Checks whether tokenization should remove whitespace from words.
 *
 * @return true if whitespace removal is enabled, false otherwise.
 */
bool Tokenizer::trim_verify() {
  return m_trim;
}

/**
 * @brief Changes the position to be checked in the token vector.
 *
 * @param val The desired position.
 */
void Tokenizer::seek(size_t val) {
  value = val;
}

/**
 * @brief Moves the token position to the next word in the token vector.
 */
void Tokenizer::next() {
  value++;
}

/**
 * @brief Moves the token position to the previous word in the token vector.
 */
void Tokenizer::prev() {
  value--;
}

/**
 * @brief Gets the size of the token list.
 *
 * @return The size of the token list.
 */
size_t Tokenizer::size() {
  return m_tokens.size();
}

/**
 * @brief Gets the current token.
 *
 * @return The current token.
 */
std::string Tokenizer::get_token() {
  return m_tokens[value];
}

/**
 * @brief Checks if the end of tokens has been reached.
 *
 * @return true if it has reached the end, false otherwise.
 */
const bool Tokenizer::end() {
  return value >= m_tokens.size();
}

/**
 * @brief Returns a list with tokens of words without spaces.
 *
 * @return A list with tokens of words without spaces.
 */
std::vector<std::string> Tokenizer::get_tokens_list() {
  return m_tokens;
}


/**
 * @brief Adds the token to the list.
 */
void Tokenizer::set_tokens(std::string token){
  m_tokens.push_back(token);
}

/**
 * @brief Resets auxiliary variables.
 */
void Tokenizer::reset(){
  begin = 0;
  endd = 0;
  value = 0;
  m_tokens.clear();
}

int Tokenizer::size_vector(){
  return m_tokens.size();
}