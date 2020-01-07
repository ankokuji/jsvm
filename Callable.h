#ifndef CALLABLE
#define CALLABLE

#include <vector>
#include "Value.h"
#include "Interpreter.h"

using std::vector;

class Callable
{
public:
  virtual Value::Value *Call(Interpreter &interpreter, vector<Value::Value *> arguments);
  virtual int Arity();
  virtual string ToString();
};

#endif