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

#include "../include/Compiler.h"
#include "../include/Node.h"
#include "../include/Token.h"
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <unordered_set>
using namespace std;

// -----------
// Lookup sets
// -----------

// All possible variable names
unordered_set<string> var_set({"*", "o", "O", "^", "=", "x", "X", "t", "T"});

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

vector<Token> tokenizer(ifstream &ifs) {
  string input = "";
  bool in_comment = false;
  vector<Token> tokens;

  while (getline(ifs, input)) {         // Read input stream line by line
    string::iterator b = input.begin(); // Beginning char of line
    string::iterator e = input.end();   // Last char of line
    // Parsing line
    // cout << "Line: " << input << endl;
    while (b < e) {
      string c(1, *b);
      string line;
      smatch m;
      Token token;

      // Skip whitespace
      regex space("\\s");
      if (regex_match(c, m, space)) {
        ++b;
        continue;
      }

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

      // Check if function definition start
      regex fn_beg("(\\[>)...(\\]>)--\\*"); // function call ex: [>*_*]>--*
      line = (b + 10 <= e) ? string(b, b + 10) : "";
      if (!line.empty() && regex_match(line, m, fn_beg)) {
        tokens.push_back(Token(FUNCTION_BEG, line));
        b += 10;
        continue;
      }

      // Check if end of function
      regex fn_end("\\*--(<\\[)...(<\\])");
      // line for function also 7 characters -- no need to re-call
      if (!line.empty() && regex_match(line, m, fn_end)) {
        tokens.push_back(Token(FUNCTION_END, line));
        b += 10;
        continue;
      }

      // Check if assignment operator
      regex asign("\\\\\\(\\^.\\^\\)\\/");
      line = (b + 7 <= e) ? string(b, b + 7) : "";
      if (!line.empty() && regex_match(line, m, asign)) {
        tokens.push_back(Token(OPERATOR, "="));
        b += 7;
        continue;
      }

      // Check if function call
      regex r_fn("(\\[>)...(\\]>)"); // function call ex: [>*_*]>
      // line for function also 7 characters -- no need to re-call
      if (!line.empty() && regex_match(line, m, r_fn)) {
        tokens.push_back(Token(CALL, line));
        b += 7;
        continue;
      }

      // Check if variable
      unordered_set<string>::const_iterator var_it = var_set.find(c);
      if (var_it != var_set.end()) { // Check for variable name *,o,O, etc.
        tokens.push_back(Token(NAME, *var_it));
        ++b; // Advance iterator
        continue;
      }

      // Check if operator
      unordered_set<string>::const_iterator op_it = op_set.find(c);
      if (op_it != op_set.end()) { // Check for op name .
        tokens.push_back(Token(OPERATOR, *op_it, 1));
        b += (*op_it).size(); // Can either be one or two
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

      // Integer parsing
      regex num("[0-9]");
      if (regex_match(c, m, num)) {
        bool is_num = true;
        string val;
        val.push_back(*b);
        ++b;

        // Keep iterating until character is not a numeral
        while (b != e && is_num) {
          c = string(1, *b);
          if (regex_match(c, m, num)) {
            val.push_back(*b);
            ++b;
          } else
            is_num = false;
        }
        tokens.push_back(Token(NUMBER, val));
        continue;
      }

      // String parsing
      if (*b == '\"') {
        ++b;
        string::iterator x = b;
        string val;

        while (*x != '\"' && x != e) {
          ++x;
        }
        val = string(b, x);
        token._t = STRING;
        token._val = val;
        tokens.push_back(token);
        b = x; // set b to now point after string
      }
      ++b;
      //  \[]/ ..... \(o_o)/\/(o-O)/
    }
    tokens.push_back(Token(EOL, "eol"));
  }

  return tokens;
}

// ------
// parser
// ------

shared_ptr<Statement_Node> parser(vector<Token> &tokens) {
  /*
   * scope stack indicates the current level of depth.
   * For example when a function definition is encountered,
   * I want all the statements to be elements within the
   * current function definition.
   */
  stack<shared_ptr<Node>> scope;
  stack<shared_ptr<Node>> operands;
  stack<Operator_Node> operators;
  shared_ptr<Statement_Node> root(
      new Statement_Node); // Syntax Tree root
  scope.push(root);
  bool in_expression = false;
  // Build tree using Shunting-Yard Algorithm
  for (Token tok : tokens) {
    ///*if(tok._t != EOL)*/ cout << "TOK " << tok._t << " " << tok._val << endl;
    if (tok._t == EOL && in_expression) { // EOL indicates end of current statement
      if (operators.size() < 1 || operands.size() < 2)
        continue;
      // Pop operator off operator stack
      Operator_Node op(operators.top());
      operators.pop();
      // Pop two operands off stack
      shared_ptr<Node> right = operands.top();
      operands.pop();
      shared_ptr<Node> left = operands.top();
      operands.pop();
      shared_ptr<Node> statement(new Statement_Node(op, left, right));
      scope.top()->add_child(statement);
      in_expression = false;

    } else if (tok._t == OPERATOR) {
      // Build sub-trees based on operator precidence
      in_expression = true;
      while (!operators.empty() && operators.top()._priority >= tok._priority) {
        Operator_Node op(operators.top()); // Get operator
        operators.pop();

        shared_ptr<Node> right = operands.top(); // Get right expression value
        operands.pop();

        shared_ptr<Node> left = operands.top(); // Get left value
        operands.pop();

        shared_ptr<Statement_Node> statement(
            new Statement_Node(op, left, right));
        operands.push(statement);
      }
      operators.push(Operator_Node(tok._val, tok._priority));

    } else if (tok._t == NUMBER || tok._t == NAME || tok._t == STRING) {
      shared_ptr<Value_Node> value(new Value_Node(tok));
      operands.push(value);

    } else if (tok._t == CALL) {
      //TODO functin all should be able to be an operand
      // Right now only procedure calls exist... no bueno
      shared_ptr<Call_Node> tmp(new Call_Node(tok._val.substr(2, 3)));
      scope.top()->add_child(tmp);

    } else if (tok._t == FUNCTION_BEG) {
      shared_ptr<Function_Node> tmp(new Function_Node(tok._val.substr(2, 3)));
      scope.top()->add_child(tmp);
      scope.push(tmp);

    } else if (tok._t == FUNCTION_END) {
      // Create a final node for the current scope. Indicates function defintion
      // end.
      shared_ptr<Function_Node> tmp(
          new Function_Node(tok._val.substr(5, 3), true));
      scope.top()->add_child(tmp);
      scope.pop();

    } else {
      // cout << "else" << endl;
    }
  }
  return root;
}

// --------
// code_gen
// --------

void code_gen(shared_ptr<Statement_Node> root, ofstream &out) {
  AST_Visitor v(out);
  root->accept(v);
}

int main(int argc, char **argv) {
  if (argc < 2)
    return 0;
  string file_name = argv[1];
  ifstream file(file_name);
  ofstream outfile(file_name + ".c");
  string input = "";
  if (file.is_open()) {
    vector<Token> tokens(tokenizer(file));
    shared_ptr<Statement_Node> root = parser(tokens);
    code_gen(root, outfile);
  }
  return 0;
}
