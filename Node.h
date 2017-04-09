// ---------
// Node.h
// Ty Trusty
// ---------

#ifndef Node_h
#define Node_h

#include <memory>
using namespace std;

// Forward declarations
class Visitor;
class Node;
class Root_Node;     // Root node
class Operator_Node; // Right now only binary operators
class Value_Node;    // Can either be a variable name or an r-value
class Call_Node;     // Function call

/**
 * Visitor pattern abstract class
 */
class Visitor {
public:
  virtual void visit(Root_Node &) = 0;
  virtual void visit(Operator_Node &) = 0;
  virtual void visit(Node &) = 0;
  virtual void visit(Value_Node &) = 0;
  virtual void visit(Call_Node &) = 0;
  virtual ~Visitor() = 0;
};

/**
 *  Implementation of visitor
 */
class AST_Visitor : Visitor {
public:
  /**
   *  Iteratively visits and accepts the root's children
   *  @param root the source node with a list of children
   */
  void visit(Root_Node &root) { cout << " Visited root " << endl; }

  /**
   * Visits the left, then right child
   * @param op the operator node
   */
  void visit(Operator_Node &op) { cout << " visited op " << endl; }

  /**
   * Visit for identifier for value. Just prints the value
   * @param val the value node
   */
  void visit(Value_Node &val) { cout << " visited val " << endl; }

  /**
   * Visit for function call node
   * @param val the value node
   */
  void visit(Call_Node &val) { cout << " visited call " << endl; }

};

/**
 * Abstract Node class for Abstract Syntax Tree
 */
class Node {
public:
  /**
   * Vector of child node pointers
   */
  vector<unique_ptr<Node>> children;
  
  /**
   * Default constructor
   */
  Node() : children() {}

  /**
   * Abstract accept to be implemented in extensions of Node
   * @param v a visitor class
   */
  virtual void accept(Visitor &v);
  virtual ~Node() = 0;
};

/**
 * Root node to serve as base node.
 */
class Root_Node : Node {
public:
  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }
};

/**
 * Operator_Node used to represent binary operations. Element class intended to be
 * visited by visitor
 */
class Operator_Node : Node {
public:
  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }
};

/**
 * Value_Node for variable names and values. Element class intended to be visited by
 * visitor
 */
class Value_Node : Node {

public:
  string _val;
  Value_Node(string val) : _val(val) {}

  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }
};

class Call_Node : Node {
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

class If_Node : Node {};
class While_Node : Node {};
#endif // Node_h
