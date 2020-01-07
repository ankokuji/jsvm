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
  Function(Stmt::Function declaration) : _declaration(declaration){};
  Value::Value* Call(Interpreter interpreter, vector<Value::Value*> arguments)
  {
    Environment *const environment = new Environment(interpreter.environment);
    for (int i = 0; i < arguments.size(); i++)
    {
      environment->Define(_declaration._params[i]._lexeme, arguments[i]);
    }

    interpreter.executeBlock(_declaration._body, environment);
    return Value::String::New("NULL");
  }

private:
  const Stmt::Function _declaration;
};

#endif