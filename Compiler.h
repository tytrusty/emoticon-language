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
#include "Node.h"
#include "Token.h"
using namespace std;

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
Statement_Node parser(vector<Token> &tokens);
void code_gen(string input);

#endif // compiler_h
