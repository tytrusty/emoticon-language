// -----------
// Visitor.cpp
// Ty Trusty
// -----------

#include "../include/Visitor.h"
#include "../include/Node.h"
#include "../include/Token.h"
#include <iostream> // ostream
#include <string>   // string
#include <vector>   // vector

void AST_Visitor::visit(Statement_Node &root) {
  // cout << "Scope level: " << root.get_depth() << endl;
  // If children is not empty, then statement contains a list of other
  // statements
  if (root.children.size() > 0) {
    // Call for each child to print their contents
    // cout << "Root breadth: " << root.children.size() << endl;
    for (shared_ptr<Node> n : root.children) {
      cout << "NODE: " << n->children.size() << endl;
      n->accept(*this);
    }
  }
  else {
    // TODO temp lulz
    out << "int ";
    root.left->accept(*this);
    root.op.accept(*this);
    root.right->accept(*this);
    out << ";" << endl;
  }
}

/**
 * Visits the left, then right child
 * @param op the operator node
 */
void AST_Visitor::visit(Operator_Node &op) {
  cout << "Visited OP: " << op._val << endl;
  out << op._val << " ";
}

/**
 * Visit for identifier for value. Just prints the value
 * @param val the value node
 */
void AST_Visitor::visit(Value_Node &v) {
  cout << "Visited VAL: " << v._token._val << endl;
  out << v._token._val << " ";
}

/**
 * Visit for function call node
 * @param val the value node
 */
void AST_Visitor::visit(Call_Node &fn) {
  hash<string> hash_fn;
  string hash_name = "a" + to_string(hash_fn(fn._name));
  //int depth = scope_map[hash_name];//cout << " Visited CALL: " << hash_name << endl;
  // If call's depth is not deeper than 
  //TODO THIS IS NOT A VALID SOLUTION
  // NEED A LIST ASSOCIATED WITH EACH PARENT
  // You can have multiple functions/vars at the same depth value, but 
  // in a different scope. 
  out << hash_name << "();" << endl;
}

void AST_Visitor::visit(Function_Node &fn) {
  if (fn.is_end) {
    out << "}" << endl; // close function definition
    return;
  }

  // TODO add to some list
  /*
   * Since I allow hideous function names like *_* I need to convert
   * each of these to a unique and c-compileable name. So I hash it
   * and make it into a string.
   */
  hash<string> hash_fn;
  string hash_name = "a" + to_string(hash_fn(fn._name));
  scope_map[hash_name] = fn.get_depth(); 
  cout << "Visiting FUNCTION: " << hash_name << endl;
  out << "void " << hash_name << "() {" << endl;
  if (fn.children.size() > 0) {
    for (shared_ptr<Node> n : fn.children) {
      n->accept(*this);
    }
  }
}
