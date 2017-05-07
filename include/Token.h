// ---------
// Token.h
// Ty Trusty
// ---------

#ifndef Token_h
#define Token_h
#include <string>
using namespace std;
/**
 * Type of token
 */
enum Type {
  NUMBER,
  NAME,
  OPERATOR,
  CALL,
  FUNCTION_BEG,
  FUNCTION_END,
  STRING,
  EOL
};

/**
 * Token struct used by tokenizer to create token list
 */
struct Token {
  Type _t;
  string _val;
  size_t _priority;
  Token(Type t = Type(), string val = "", size_t priority = 0)
      : _t(t), _val(val), _priority(priority) {}
};

#endif
