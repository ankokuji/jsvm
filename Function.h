#ifndef JS_FUNCTION
#define JS_FUNCTION

#include "Callable.h"
#include "Stmt.h"
#include "Value.h"
#include "Interpreter.h"
#include <list>
#include <vector>

using std::list;
using std::vector;

class Function : public Callable
{
public:
  Function(Stmt::Function declaration, Environment *closure)
      : _declaration(declaration), _closure(closure){};
  Value::Value *Call(Interpreter &interpreter, vector<Value::Value *> arguments) override
  {
    Environment *const environment = new Environment(_closure);
    for (int i = 0; i < arguments.size(); i++)
    {
      environment->Define(_declaration._params[i]._lexeme, arguments[i]);
    }

    interpreter.executeBlock(_declaration._body, environment);
    return Value::String::New("NULL");
  }
  int Arity() override
  {
    return _declaration._params.size();
  }
  string ToString() override
  {
    return "<fn " + _declaration._name._lexeme + ">";
  }

private:
  Environment *_closure;
  const Stmt::Function _declaration;
};

#endif