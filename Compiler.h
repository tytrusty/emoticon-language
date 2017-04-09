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
  NUM,
  NAME,
  OPERATOR,
  FUNCTION,
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
  Token(Type t = Type(), string val = "") : _t(t), _val(val) {}
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
