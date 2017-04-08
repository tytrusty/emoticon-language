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
#include <regex> // regex, smatch
using namespace std;

// -----------
// Lookup sets
// -----------

// All possible variable names
unordered_set<string> var_set({"*", "o", "O", "^", "\"", "="});

// Operators
unordered_set<string> op_set({
    "_", // assignment
    "-", // range
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
  int counter = 0;
  while (getline(ifs, input)) {         // Read input stream line by line
    string::iterator b = input.begin(); // Beginning char of line
    string::iterator e = input.end();   // Last char of line
    // Parsing line
    cout << "Line: " << input << endl;
    while (b != e) {
      cout << "b: " << *b << endl;
      string c(1, *b);
      smatch m;
      // Check if operator or variable
      unordered_set<string>::const_iterator var_it = var_set.find(c);
      unordered_set<string>::const_iterator op_it = op_set.find(c);
      /*
       * Regex done in else statement to avoid unwanted regex matching if the
       * character is an operator or variable
       */
      if (var_it != var_set.end()) { // Check for variable name *,o,O, etc.
        ++b; // Advance iterator

      } else if (op_it != op_set.end()) { // Check for op name .
        ++b; // Advance iterator

      } else {
        // Test if set of characters is a function
        regex r_fn("(\\[>)...(\\]>)"); // function call ex: [>*_*]>
        string fn = (b + 7 <= e) ? string(b, b + 7) : "";
        if (!fn.empty() && regex_match(fn, m, r_fn)) {
          cout << "function match" << endl;
          b += 7; 
        } else 
          ++b;
///// \[]/ ..... \(o_o)/\/(o-O)/
        regex comment_one("(\\(#).(#\\))"); // one-line comment
        regex comment_begin("");            // multi-line comment begin
        regex comment_end("");              // multi-line comment end
      }
    }
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
