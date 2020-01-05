#ifndef INTERPRETER
#define INTERPRETER

#include "Expr.h"
#include "Stmt.h"
#include <list>

using std::list;

class Interpreter : public Expr::Visitor, public Stmt::Visitor
{
public:
  void interprete(list<Stmt::Stmt> stmt)
  {
  }

  Value::Value interprete(Expr::Expr expr) {
    return expr.accept(*this);
  }
};

#endif