// ----------
// compiler.h
// Ty Trusty
// -----------

#ifndef compiler_h
#define compiler_h

#include <fstream>       // ifstream
#include <iostream>      // cin, cout
#include <regex>         // regex, smatch
#include <string>        // string
#include <unordered_set> // unordered_set
using namespace std;

/**
 * Type of token
 */
enum Type {
  NUMBER,
  NAME,
  OPERATOR,
  CALL,
  FUNCTION_BEG,
  FUNCTION_END,
  STRING,
  EOL
};

/**
 * Token struct used by tokenizer to create token list
 */
struct Token {
  Type _t;
  string _val;
  size_t _priority;
  Token(Type t = Type(), string val = "", size_t priority = 0) : _t(t), _val(val), _priority(priority) {}
};

/**
 * Reads from input stream and produces a list of the tokens with their
 * associate types and values. Returns a list of the tokens ordered
 * chronologically.
 * @param ifs a file input stream to read from
 */
vector<Token> tokenizer(ifstream &ifs);

/**
 * Parses the token list and produces an Abstract Syntax Tree
 * @param tokens a vector containing token structs
 */
void parser(vector<Token> &tokens);
void code_gen(string input);

#endif // compiler_h
