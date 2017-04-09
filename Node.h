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
class Statement_Node;     // Statement node
class Operator_Node; // Right now only binary operators
class Value_Node;    // Can either be a variable name or an r-value
class Call_Node;     // Function call

/**
 * Abstract Node class for Abstract Syntax Tree
 */
class Node {
public:
  /**
   * Vector of child node pointers
   */
  vector<Node> children;

  /**
   * Default constructor
   */
  Node() : children() {}

  /**
   * Abstract accept to be implemented in extensions of Node
   * @param v a visitor class
   */
  virtual void accept(Visitor &v) {};
  virtual ~Node() {};
};

/**
 * Statement node to serve as base nodes.
 */
class Statement_Node : public Node {
public:
  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }
  ~Statement_Node() = default;
};

/**
 * Operator_Node used to represent binary operations. Element class intended to be
 * visited by visitor
 */
class Operator_Node : public Node {
public:
  string _val;
  size_t _priority;
  Operator_Node(string val, size_t priority = 1) : _val(val), _priority(priority) {}
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
class Value_Node : public Node {

public:
  string _val;
  Value_Node(string val) : _val(val) {}

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

/**
 * Visitor pattern abstract class
 */
class Visitor {
public:
  /*virtual void visit(Statement_Node &) = 0;
  virtual void visit(Operator_Node &) = 0;
  virtual void visit(Node &) = 0;
  virtual void visit(Value_Node &) = 0;
  virtual void visit(Call_Node &) = 0;
  */
  virtual void visit(Statement_Node &) {}
  virtual void visit(Operator_Node &) {}
  virtual void visit(Node &) {}
  virtual void visit(Value_Node &) {}
  virtual void visit(Call_Node &) {}
  virtual ~Visitor() {}
};

/**
 *  Implementation of visitor
 */
class AST_Visitor : public Visitor {
public:
  /**
   *  Iteratively visits and accepts the root's children
   *  @param root the source node with a list of children
   */
  void visit(Statement_Node &root) { 
    cout << " Visited root " << endl; 
    root.child[0].accept(*this);
  }

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

#endif // Node_h
