#ifndef INTERPRETER_SCOPE
#define INTERPRETER_SCOPE

#include "Interpreter.h";

class Scope
{
public:
  Scope(Interpreter *interpreter, Environment *env) : _previous_env(interpreter->environment), _interpreter(interpreter)
  {
    interpreter->environment = env;
  }

  ~Scope()
  {
    _interpreter->environment = _previous_env;
  }

private:
  Interpreter *_interpreter;
  Environment *_previous_env;
};

#endif