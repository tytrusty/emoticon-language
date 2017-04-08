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

#include <string>        // string
#include <unordered_set> // unordered_set
#include <fstream>       // ifstream
#include <iostream>      // cin, cout
using namespace std;

unordered_set<char> var_set({'*', 'o', 'O', '^', '\'', '='});
unordered_set<char> op_set({'_','-',';','.'});
enum Type { PAREN, NUM, STRING};
struct Token_Type {
  Type t;


};


// ---------
// tokenizer
// ---------

void tokenizer(ifstream& ifs) {
  string input = "";
  while(getline(ifs, input)) {
    cout << "I: " << input << endl;
  }
  int counter = 0;
  string::iterator b = input.begin();
  string::iterator e = input.end();
  while(b != e) {
    unordered_set<char>::const_iterator var_it = var_set.find(*b);
    unordered_set<char>::const_iterator op_it = op_set.find(*b);

    if(var_it != var_set.end()) { // Check for variable name *,o,O, etc.
      continue;
    }
    if(op_it != op_set.end()) { // Check for op name .
      continue;
    }
    



  }
}


// ------
// parser
// ------

void parser(string input) {

}


// ---------
// transform
// ---------

void transform(string input) {

}

// --------
// code_gen
// --------

void code_gen(string input) {

}

int main(int argc, char** argv) {
  string file_name = argv[1];
  ifstream file(file_name);
  string input = "";
  if(!file.good())
    cout << "bad file read" << endl;

  while(getline(file, input)) {
    cout << "I: " << input << endl;
  }
  //if(file.is_open()) 
  //  tokenizer(file);
  return 0;
}



