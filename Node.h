// ---------
// Node.h
// Ty Trusty
// ---------

#ifndef Node_h
#define Node_h

#include "Token.h"
#include <memory>
using namespace std;

// Forward declarations
class Visitor;
class Node;
class Statement_Node; // Statement node
class Operator_Node;  // Right now only binary operators
class Value_Node;     // Can either be a variable name or an r-value
class Call_Node;      // Function call

/**
 * Visitor pattern abstract class
 */
class Visitor {
public:
  virtual void visit(Statement_Node &) {}
  virtual void visit(Operator_Node &) {}
  virtual void visit(Node &) {}
  virtual void visit(Value_Node &) {}
  virtual void visit(Call_Node &) {}
  virtual ~Visitor() {}
};


/**
 * Abstract Node class for Abstract Syntax Tree
 */
class Node {
public:
  /**
   * Vector of child node pointers
   */
  vector<shared_ptr<Node>> children;

  /**
   * Abstract accept to be implemented in extensions of Node
   * @param v a visitor class
   */
  virtual void accept(Visitor &v) { cout << " Visited Node " << endl; };

  /**
   * Default constructor
   */
  Node() : children() {}
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
  Operator_Node op;
  shared_ptr<Node> left;
  shared_ptr<Node> right;

  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }

  /**
   * Default constructor
   */
  Statement_Node(Operator_Node o = Operator_Node(), shared_ptr<Node> lhs = nullptr, shared_ptr<Node> rhs = nullptr) : op(o), left(lhs), right(rhs) {}
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

/**
 *  Implementation of visitor
 */
class AST_Visitor : public Visitor {
public:
  ofstream& out;
  AST_Visitor(ofstream& output) : out(output) {}

  /**
   *  Iteratively visits and accepts the root's children
   *  @param root the source node with a list of children
   */
  void visit(Statement_Node &root) {
    // If children is not empty, then statement contains a list of other statements
    if (root.children.size() > 0) {
      // Call for each child to print their contents
      for (shared_ptr<Node> n : root.children) {
        cout << "NODE: " << n->children.size() << endl;
        n->accept(*this);
      }
    } else {
      //TODO temp lulz
      out << "int ";
      root.left ->accept(*this);
      root.op.accept(*this);
      root.right->accept(*this);
      out << ";" << endl;
    }
  }

  /**
   * Visits the left, then right child
   * @param op the operator node
   */
  void visit(Operator_Node &op) { out << op._val << " "; }

  /**
   * Visit for identifier for value. Just prints the value
   * @param val the value node
   */
  void visit(Value_Node &v) { out << v._token._val << " "; }

  /**
   * Visit for function call node
   * @param val the value node
   */
  void visit(Call_Node &val) { cout << " visited call " << endl; }
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

class Function_Node : public Node {
public:
  string _name;
  /**
   * Default constructor
   * @param name the function call name
   */
  Function_Node(string name) : _name(name) {}

  /**
   * Accept method as part of the visitor design patern.
   * @param v the visitor that this node is passed into
   */
  void accept(Visitor &v) { v.visit(*this); }
};
class If_Node : public Node {};
class While_Node : public Node {};

#endif // Node_h
