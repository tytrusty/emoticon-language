// ---------
// Node.h
// Ty Trusty
// ---------

#ifndef Node_h
#define Node_h

#include "Token.h"
#include <fstream>       // ifstream
#include <memory>
#include <vector>
#include <iostream>
#include <string> 
using namespace std;

// Forward declarations
class Visitor;
class Node;
class Statement_Node; // Statement node
class Operator_Node;  // Right now only binary operators
class Value_Node;     // Can either be a variable name or an r-value
class Call_Node;      // Function call
class Function_Node;
class AST_Visitor;

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
  virtual void visit(Function_Node &) {}
  virtual ~Visitor() {}
};

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
  void visit(Statement_Node &root) {
    // If children is not empty, then statement contains a list of other
    // statements
    if (root.children.size() > 0) {
      // Call for each child to print their contents
      //cout << "Root breadth: " << root.children.size() << endl;
      for (shared_ptr<Node> n : root.children) {
        cout << "NODE: " << n->children.size() << endl;
        n->accept(*this);
      }
    } else {
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
  void visit(Operator_Node &op) {
    cout << "Visited OP: " << op._val << endl;
    out << op._val << " ";
  }

  /**
   * Visit for identifier for value. Just prints the value
   * @param val the value node
   */
  void visit(Value_Node &v) {
    cout << "Visited VAL: " << v._token._val << endl;
    out << v._token._val << " ";
  }

  /**
   * Visit for function call node
   * @param val the value node
   */
  void visit(Call_Node &val) { std::cout << " visited call " << endl; }

  void visit(Function_Node &fn) {
    cout << "Visiting fn: " << fn._name << endl;
    if(fn.is_end) {
      out << "}" << endl; // close function definition 
      return;
    }
    
    //TODO add to some list
    /* 
     * Since I allow hideous function names like *_* I need to convert
     * each of these to a unique and c-compileable name. So I hash it
     * and make it into a string. 
     */
    hash<string> hash_fn;
    string hash_name = "a" + to_string(hash_fn(fn._name));
    out << "void " << hash_name << "() {" << endl;
    if (fn.children.size() > 0) {
      for (shared_ptr<Node> n : fn.children) {
        n->accept(*this);
      }
    }
    
  }
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
