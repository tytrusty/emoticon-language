// ----------
// node.h
// Ty Trusty
// -----------

#ifndef Node_h
#define Node_h
using namespace std;

// Forward declarations
class Visitor;
class Node;
class Root;

/**
 * Visitor pattern abstract class
 */
class Visitor {
  public:
    virtual void visit(Root& root) = 0;  
    virtual ~Visitor() = 0;
};

class AST_Visitor : Visitor {
  public:
    void visit(Root& root){
      cout << " Visited root " << endl;
    }
};

/**
 *
 */
class Node {
  public:
    virtual void enter(Visitor& v);
    virtual ~Node() = 0;
};

/**
 *
 */
class Root : Node {
  public:
    void enter(Visitor& v) {
      v.visit(*this);
    }
};

/**
 *
 */



#endif // Node_h
