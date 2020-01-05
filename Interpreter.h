#ifndef INTERPRETER
#define INTERPRETER

#include "Expr.h"
#include "Stmt.h"
#include <list>

using std::list;

class Interpreter : public Decl::Expr, public Stmt::Stmt
{
public:
  void interprete(list<Stmt::Stmt> stmt)
  {
  }

  void interprete(Decl::Expr expr) {
    return expr.accept(this);
  }
};

#endif