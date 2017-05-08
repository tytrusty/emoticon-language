// ---------
// Visitor.h
// Ty Trusty
// ---------

#ifndef Visitor_h
#define Visitor_h

#include "Token.h" // Token
#include <fstream> // ifstream
//#include <memory>
//#include <vector>
//#include <iostream>
#include <string>

// Forward declarations
class Visitor;
class Node;           // Abstract node class
class Statement_Node; // Statement node
class Operator_Node;  // Right now only binary operators
class Value_Node;     // Can either be a variable name or an r-value
class Call_Node;      // Function call
class Function_Node;  // Function definition begin or end

/**
 * Visitor pattern abstract class
 */
class Visitor {
public:
  virtual void visit(Statement_Node &) = 0;
  virtual void visit(Operator_Node &) = 0;
  virtual void visit(Function_Node &) = 0;
  virtual void visit(Value_Node &) = 0;
  virtual void visit(Call_Node &) = 0;
  virtual ~Visitor() {}
};

/**
 *  Implementation of visitor
 */
class AST_Visitor : public Visitor {
public:
  ofstream &out;
  AST_Visitor(ofstream &output) : out(output) {}

  /**
   *  Iteratively visits and accepts the root's children
   *  @param root the source node with a list of children
   */
  void visit(Statement_Node &root);

  /**
   * Visits the left, then right child
   * @param op the operator node
   */
  void visit(Operator_Node &op);

  /**
   * Visit for identifier for value. Just prints the value
   * @param val the value node
   */
  void visit(Value_Node &v);

  /**
   * Visit for function call node
   * @param val the value node
   */
  void visit(Call_Node &val);

  void visit(Function_Node &fn);
};
#endif
