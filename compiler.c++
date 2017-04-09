// -------------------------------------------------------------//
// By Ty                                                        //
// 4/08/2017                                                    //
// License:                                                     //
// do What The Fuck you want to Public License                  //
//                                                              //
// Version 1.0, March 2000                                      //
// Copyright (C) 2000 Banlu Kemiyatorn (]d).                    //
// 136 Nives 7 Jangwattana 14 Laksi Bangkok                     //
// Everyone is permitted to copy and distribute verbatim copies //
// of this license document, but changing it is not allowed.    //
//				                                                //
// Ok, the purpose of this license is simple                    //
// and you just                                                 //
//                                                              //
// DO WHAT THE FUCK YOU WANT TO.                                //
// -------------------------------------------------------------//

#include "compiler.h"
#include "node.h"
using namespace std;

// -----------
// Lookup sets
// -----------

// All possible variable names
unordered_set<string> var_set({"*", "o", "O", "^", "\"", "=", "x", "X", "t",
                               "T"});

// Operators
unordered_set<string> op_set({
    "_", // addition
    "-", // subtraction
    ";", // division
    ".", // multiplication
    "<", // less than
    ">", // greater than
    "<>" // equals
});

// ---------
// tokenizer
// ---------

void tokenizer(ifstream &ifs) {
  string input = "";
  bool in_comment = false;
  vector<Token> tokens;

  while (getline(ifs, input)) {         // Read input stream line by line
    string::iterator b = input.begin(); // Beginning char of line
    string::iterator e = input.end();   // Last char of line
    // Parsing line
    cout << "Line: " << input << endl;
    while (b < e) {
      string c(1, *b);
      string line;
      smatch m;
      Token token;

      // If currently in a multi-line comment, only look for end marker
      if (in_comment) {
        regex comment_end("\\*--(\\(#).(#\\))"); // multi-line comment end
        line = (b + 8 <= e) ? string(b, b + 8) : "";
        if (!line.empty() && regex_match(line, m, comment_end)) {
          in_comment = false;
          b += 8;
          continue;
        }
        ++b;
        continue;
      }

      cout << "b: " << *b << endl;

      // Check if function definition start
      regex fn_beg("(\\[>)...(\\]>)--\\*"); // function call ex: [>*_*]>--*
      line = (b + 10 <= e) ? string(b, b + 10) : "";
      if (!line.empty() && regex_match(line, m, fn_beg)) {
        b += 7;
        token._t = FUNCTION_BEG;
        token._val = line;
        tokens.push_back(token);
        b += 10;
        continue;
      }
      // Check if end of function
      regex fn_end("\\*--(<\\[)...(<\\])");
      // line for function also 7 characters -- no need to re-call
      if (!line.empty() && regex_match(line, m, fn_end)) {
        token._t = FUNCTION_END;
        token._val = line;
        tokens.push_back(token);
        b += 10;
        continue;
      }

      // Check if assignment operator
      regex asign("\\\\\\(\\^.\\^\\)\\/");
      line = (b + 7 <= e) ? string(b, b + 7) : "";
      if (!line.empty() && regex_match(line, m, asign)) {
        token._t = OPERATOR;
        token._val = line;
        tokens.push_back(token);
        b += 7;
        continue;
      }

      // Check if function call
      regex r_fn("(\\[>)...(\\]>)"); // function call ex: [>*_*]>
      // line for function also 7 characters -- no need to re-call
      if (!line.empty() && regex_match(line, m, r_fn)) {
        b += 7;
        token._t = FUNCTION;
        token._val = line;
        tokens.push_back(token);
        b += 7;
        continue;
      }

      // Check if variable
      unordered_set<string>::const_iterator var_it = var_set.find(c);
      if (var_it != var_set.end()) { // Check for variable name *,o,O, etc.
        token._t = NAME;
        token._val = *b;
        tokens.push_back(token);
        ++b; // Advance iterator
        continue;
      }

      // Check if operator
      unordered_set<string>::const_iterator op_it = op_set.find(c);
      if (op_it != op_set.end()) { // Check for op name .
        token._t = OPERATOR;
        token._val = *b;
        tokens.push_back(token);
        ++b; // Advance iterator
        continue;
      }

      // Check if multi-line comment begin
      regex comment_begin("(\\(#).(#\\))--\\*"); // multi-line comment begin
      line = (b + 8 <= e) ? string(b, b + 8) : "";
      if (!line.empty() && regex_match(line, m, comment_begin)) {
        // Ignore everything until end indicator reached
        in_comment = true;
        b += 8;
        continue;
      }

      // Check if one-line comment
      regex comment_one("(\\(#).(#\\))");
      line = (b + 5 <= e) ? string(b, b + 5) : "";
      if (!line.empty() && regex_match(line, m, comment_one)) {
        break; // If one-line comment, move onto next line
      }

      ++b;
      //  \[]/ ..... \(o_o)/\/(o-O)/
    }
    tokens.push_back(Token(EOL, "eol"));
  }

  for (Token i : tokens) {
    cout << "TOK " << i._t << " " << i._val << endl;
  }
}

// ------
// parser
// ------

void parser(string input) {}

// ---------
// transform
// ---------

void transform(string input) {}

// --------
// code_gen
// --------

void code_gen(string input) {}

int main(int argc, char **argv) {
  string file_name = argv[1];
  ifstream file(file_name);
  string input = "";
  if (file.is_open())
    tokenizer(file);
  return 0;
}
