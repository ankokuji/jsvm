#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <map>
#include <string>
#include "Value.h"
#include "Error.h"
#include "Lexer.h"

using std::string;

typedef Value::Value val;

class Environment
{
public:
  Environment() : enclosing(nullptr){};
  Environment(Environment *env) : enclosing(env){};
  void Define(string name, val *value)
  {
    values[name] = value;
  }
  val *Get(Token name) const
  {
    auto iter = values.find(name._lexeme);
    if (iter == values.end())
    {
      if (!enclosing)
      {
        throw runtime_error("Undefined variable '" + name._lexeme + "'.");
      } else {
        return enclosing->Get(name);
      }
    }
    return (*iter).second;
  }
  Environment *const enclosing;

private:
  std::map<string, val *> values;
};

#endif