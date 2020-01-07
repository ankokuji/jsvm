#ifndef CALLABLE
#define CALLABLE

#include <list>
#include "Value.h"
#include "Interpreter.h"

class Callable
{
public:
  virtual Value::Value *call(Interpreter &interpreter, list<Value::Value *> arguments);
  virtual int arity();
};

#endif