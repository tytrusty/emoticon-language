// ---------
// Node.h
// Ty Trusty
// ---------

#ifndef Node_h
#define Node_h

#include <fstream>   // ifstream
#include <memory>    // shared_ptr
#include <vector>    // vector
#include <iostream>  // ostream
#include <string>    // string 
#include "Token.h"
#include "Visitor.h"
using namespace std;

/**
 * Abstract Node class for Abstract Syntax Tree
 */
class Node {

  friend AST_Visitor;

public:
  /**
   * Vector of child node pointers
   */
  vector<shared_ptr<Node>> children;

public:
  /**
   * Abstract accept to be implemented in extensions of Node
   * @param v a visitor class
   */
  virtual void accept(Visitor &v) { cout << " Visited Node " << endl; };

  /**
   * Adds node to children vector
   * @param node to be added
   */
  void add_child(shared_ptr<Node> node) { children.push_back(node); }

  /**
   * Default constructor
   */
  Node() : children() {}

  /**
   * Default destructor
   */
  virtual ~Node(){};
};

/**
 * Operator_Node used to represent binary operations. Element class intended to
 * be
 * visited by visitor
 */
class Operator_Node : public Node {
public:
  string _val;
  size_t _priority;
  Operator_Node(string val = "", size_t priority = 1)
      : _val(val), _priority(priority) {}
  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }
};

/**
 * Statement node to serve as base nodes.
 */
class Statement_Node : public Node {
public:
  /**
   * operator in expression
   */
  Operator_Node op;
  
  /**
   * left operand in expression
   */
  shared_ptr<Node> left;

  /**
   * right operand in expression
   */
  shared_ptr<Node> right;

  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }

  /**
   * Default constructor
   */
  Statement_Node(Operator_Node o = Operator_Node(),
                 shared_ptr<Node> lhs = nullptr, shared_ptr<Node> rhs = nullptr)
      : op(o), left(lhs), right(rhs) {}
  
  ~Statement_Node() = default;
};

/**
 * Value_Node for variable names and values. Element class intended to be
 * visited by
 * visitor
 */
class Value_Node : public Node {

public:
  Token _token;
  Value_Node(Token token) : _token(token) {}

  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }
};

class Function_Node : public Node {
public:
  /**
   * String identifier for this node. 
   */
  string _name;
  
  /*
   * Indicates if this node represents the end of a function definition.
   */
  bool is_end; 

  /**
   * Default constructor
   * @param name the function call name
   */
  Function_Node(string name, bool end = false) : _name(name), is_end(end) {}

  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }
};

class Call_Node : public Node {
public:
  string _name;
  /**
   * Default constructor
   * @param name the function call name
   */
  Call_Node(string name) : _name(name) {}

  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }
};

class If_Node : public Node {};
class While_Node : public Node {};

#endif // Node_h
