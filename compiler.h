// ----------
// compiler.h
// Ty Trusty
// -----------

#ifndef compiler_h
#define compiler_h

#include <fstream>       // ifstream
#include <iostream>      // cin, cout
#include <string>        // string
#include <unordered_set> // unordered_set
using namespace std;

/**
 * Type of token
 */
enum Type { PAREN, NUM, STRING };

/**
 * Token struct used by tokenizer to create token list
 */
struct Token_Type {
  Type t;
};

void tokenizer(ifstream &ifs);
void parser(string input);
void transform(string input);
void code_gen(string input);

#endif // compiler_h
