#ifndef INTERPRETER
#define INTERPRETER

#include "Expr.h"
#include "Stmt.h"
#include "Environment.h"
#include "Scope.h"
#include <list>

using std::list;

class Interpreter : public Expr::Visitor, public Stmt::Visitor
{
public:
  void interprete(list<Stmt::Stmt> stmt)
  {
  }

  Value::Value interprete(Expr::Expr expr)
  {
    return expr.accept(*this);
  }

  void executeBlock(vector<Stmt::Stmt> statements, Environment *environment)
  {
    // Environment previous = this->environment;
    // this->environment = &environment;
    Scope env_scope(this, environment);

    for (Stmt::Stmt statement : statements)
    {
      execute(statement);
    }
  }
  Environment *const globals = new Environment();
  Environment *environment = globals;

private:
  void execute(Stmt::Stmt stmt)
  {
    stmt.accept(this);
  }
};

#endif