// ----------
// compiler.h
// Ty Trusty
// -----------

#ifndef compiler_h
#define compiler_h

#include <iostream>      // cin, cout
#include <fstream> // ifstream
#include <regex>   // regex, smatch
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

void tokenizer(ifstream &ifs);
void parser(string input);
void transform(string input);
void code_gen(string input);

#endif // compiler_h
