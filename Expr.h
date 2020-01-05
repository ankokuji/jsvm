
#ifndef DECL_EXP
#define DECL_EXP

#include "Lexer.h"
#include "Value.h"
#include <vector>

using std::vector;

namespace Expr
{

class Visitor;

enum ExprType
{
  BINARY,
  ASSIGN,
  VARIABLE,
  GROUPING
};

class Expr
{

private:
  friend class Parser;
  enum ExprType _type;

protected:
  Expr(ExprType type) : _type(type){};

public:
  ExprType getType()
  {
    return _type;
  }
  virtual Value::Value accept(Visitor visitor);
};

class Binary : public Expr
{
public:
  Expr _left;
  Token _op;
  Expr _right;

  Binary(Expr left, Token op, Expr right) : Expr(BINARY), _op(op), _left(left), _right(right){};
  Value::Value accept(Visitor visitor) override
  {
    return visitor.visitBinaryExpr(*this);
  }
};

class Assign : public Expr
{
  Assign(Token name, Expr value) : Expr(ASSIGN), _name(name), _value(value) {}
  Token _name;
  Expr _value;

  Value::Value accept(Visitor visitor) override
  {
    return visitor.visitAssignExpr(*this);
  }
};

class Call : public Expr
{
  Call(Expr callee, Token paren, vector<Expr> arguments)
      : _callee(callee), _paren(paren), _arguments(arguments) {}

  Expr _callee;
  Token _paren;
  vector<Expr> _arguments;
};

class Grouping : public Expr
{
public:
  Grouping(Expr expression) : Expr(GROUPING), _expression(expression) {}
  Expr _expression;
};

template <typename T>
class Literal : public Expr
{
  T _value;

public:
  Literal(T value) : _value(value)
};

class Logical : public Expr
{
  Logical(Expr left, Token op, Expr right)
      : _left(left), _op(op), _right(right) {}

  Expr _left;
  Token _op;
  Expr _right;
};

class Unary : public Expr
{
public:
  Token _op;
  Expr _right;

  Unary(Token op, Expr right) : _op(op), _right(right) {}
};

class Variable : public Expr
{
  Variable(Token name) : Expr(VARIABLE), _name(name){};

  Value::Value accept(Visitor visitor)
  {
    return visitor.visitVariableExpr(*this);
  }

  Token _name;
};

typedef valptr valptr;

class Visitor
{
public:
  virtual valptr visitAssignExpr(Assign expr);
  virtual valptr visitBinaryExpr(Binary expr);
  virtual valptr visitCallExpr(Call expr);
  virtual valptr visitGetExpr(Get expr);
  virtual valptr visitGroupingExpr(Grouping expr);
  virtual valptr visitLiteralExpr(Literal expr);
  virtual valptr visitLogicalExpr(Logical expr);
  virtual valptr visitSetExpr(Set expr);
  virtual valptr visitSuperExpr(Supevirtual expr);
  virtual valptr visitThisExpr(This expr);
  virtual valptr visitUnaryExpr(Unary expr);
  virtual valptr visitVariableExpr(Variable expr);
};

}; // namespace Decl

#endif