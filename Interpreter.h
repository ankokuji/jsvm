#ifndef INTERPRETER
#define INTERPRETER

#include "Expr.h"
#include "Stmt.h"
#include "Environment.h"
#include "Scope.h"
#include "Function.h"
#include <list>

using std::list;

class Interpreter : public Expr::Visitor, public Stmt::Visitor
{
public:
  Environment *const globals = new Environment();
  Environment *environment = globals;
  void interprete(list<Stmt::Stmt> stmt)
  {
  }

  Value::Value interprete(Expr::Expr expr)
  {
    return expr.accept(*this);
  }

public:
  void visitFunctionStmt(Stmt::Function stmt)
  {
    Function function(stmt, environment);
    Value::Function* func = Value::Function::New(function);
    environment->Define(stmt._name._lexeme, func);
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

private:
  void execute(Stmt::Stmt stmt)
  {
    stmt.accept(this);
  }
};

#endif