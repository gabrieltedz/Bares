#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include <optional>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>

using std::quoted;
using namespace std;

/**
 * @brief The Tokenizer class for text tokenization.
 */
class Tokenizer
{
private:
    string m_input;                      /*!< Original string. */
    string m_delimit;                    /*!< Delimiters. */
    bool m_trim;                              /*!< Flag indicating whether to remove spaces from words. */
    vector<string> m_tokens;        /*!< Separated words from the text. */

public:
    /**
     * @brief Default constructor for the Tokenizer class.
     */
    Tokenizer() {}

    /// Auxiliary variables
    size_t begin{0};                        /*!< Start of the vector. */
    size_t endd{0};                         /*!< End of the vector. */
    size_t value{0};                        /*!< Position in the vector. */
    std::string token;                      /*!< Each word. */
    
    int size_vector(); // Tamanho do vector 

    /**
     * @brief Function to split each word without spaces.
     *
     * @param m_input The text to be split.
     * @param m_delimit The delimiter for each word.
     * @param m_trim Flag to indicate whether to remove spaces between words.
     */
    void tokens(string m_input, string m_delimit, bool m_trim);

    /**
     * @brief Checks whether spaces should be removed from words.
     * @return true if spaces should be removed from words.
     */
    bool trim_verify();

    /**
     * @brief Moves the token position to a specific value.
     * @param val The value to which the token position will be moved.
     */
    void seek(size_t val);

    /**
     * @brief Moves the token position to the next word.
     */
    void next();

    /**
     * @brief Moves the token position to the previous word.
     */
    void prev();

    /**
     * @brief Gets the size of the token list.
     * @return The size of the token list.
     */
    size_t size();

    /**
     * @brief Gets the current token.
     * @return The current token.
     */
    std::string get_token();

    /**
     * @brief Checks if the end of tokens has been reached.
     * @return true if the end has been reached, false otherwise.
     */
    const bool end();

    /**
     * @brief Returns a list of tokens without spaces.
     * @return A list of tokens without spaces.
     */
    vector<string> get_tokens_list();

    /**
     * @brief Sets a token.
     * @param token The token to be set.
     */
    void set_tokens(string token);

    /**
     * @brief Resets the token position and other auxiliary variables.
     */
    void reset();
};

/*
int main() {
  {
    std::string line{ "12 , 4; 5,  100,  3" };

    std::cout << ">> Original string: " << std::quoted(line) << "\n\n";

    Tokenizer tk(line);

    std::vector<std::string> lista = tk.get_tokens_list();



    std::cout << ">> Forward traversing:\n";
    while (not tk.end()) {
      if (tk.get_token()) {
        std::cout << std::quoted(*tk.get_token()) << " "; // tk.get_token().value()
        tk.next();
      }
    }
    std::cout << "\n>> Reverse traversing:\n";
    tk.seek(tk.size() - 1);
      if (tk.get_token()) {
        std::cout << "-- Current token is " << std::quoted(*tk.get_token()) << '\n';
        tk.prev();
      }
    
  }

  {
    std::string line{ "  São Paulo  , João  Pessoa,   Recife, Boa  Vista   , Natal 3  " };
    std::cout << "\n\n>> Original string: " << std::quoted(line) << "\n\n";

    Tokenizer tk( line, "", false );
    std::cout << ">> Forward traversing:\n";
    while (not tk.end()) {
      if (tk.get_token()) {
        std::cout << "-- Current token is " << std::quoted(*tk.get_token()) << '\n';
        tk.next();
      }
    }
  }

  return 0;
}
*/

#endif //_TOKENIZER_H_