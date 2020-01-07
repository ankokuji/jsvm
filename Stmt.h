#ifndef STMT
#define STMT

#include "Lexer.h"
#include "Expr.h"
#include <vector>

using std::list;
using std::vector;

namespace Stmt
{

typedef void visitor_return;

class Visitor;

class Stmt
{
public:
  virtual visitor_return accept(Visitor *visitor);
};

// class Class : public Stmt
// {
//   Class(Token name,
//         Expr::Variable superclass,
//         vector<Stmt::Function> methods)
//   {
//     this.name = name;
//     this.superclass = superclass;
//     this.methods = methods;
//   }

//   template <typename R>
//   R accept(Visitor<R> visitor)
//   {
//     return visitor.visitClassStmt(this);
//   }

//   Token name;
//   Expr.Variable superclass;
//   List<Stmt.Function> methods;
// };

class Function : public Stmt
{
public:
  Function(Token name, vector<Token> params, vector<Stmt> body)
      : _name(name), _params(params), _body(body){};
  visitor_return accept(Visitor *visitor) override
  {
    return visitor->visitFunctionStmt(*this);
  }
  Token _name;
  vector<Token> _params;
  vector<Stmt> _body;
};

class Visitor
{
public:
  visitor_return visitBlockStmt(Block stmt);
  visitor_return visitClassStmt(Class stmt);
  visitor_return visitExpressionStmt(Expression stmt);
  visitor_return visitFunctionStmt(Function stmt);
  visitor_return visitIfStmt(If stmt);
  visitor_return visitPrintStmt(Print stmt);
  visitor_return visitReturnStmt(Return stmt);
  visitor_return visitVarStmt(Var stmt);
  visitor_return visitWhileStmt(While stmt);
};
} // namespace Stmt

#endif