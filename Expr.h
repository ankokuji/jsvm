
#ifndef DECL_EXP
#define DECL_EXP

#include "Lexer.h"
#include <vector>

using std::vector;

namespace Decl
{

enum DeclType
{
  BINARY,
  ASSIGN,
  VARIABLE
};

class Expr
{
  friend class Parser;
  enum DeclType _type;

protected:
  Expr(DeclType type) : _type(type){};

public:
  DeclType getType()
  {
    return _type;
  }
};

class Binary : public Expr
{
public:
  Expr _left;
  Token _op;
  Expr _right;

  Binary(Expr left, Token op, Expr right) : Expr(BINARY), _op(op){};

  template <typename R>
  R accept(Visitor<R> visitor) override
  {
    return visitor.visitAssignExpr(this);
  }
};

class Assign : public Expr
{
  Assign(Token name, Expr value) : Expr(ASSIGN), _name(name), _value(value) {}
  Token _name;
  Expr _value;

  template <typename R>
  R accept(Visitor<R> visitor)
  {
    return visitor.visitAssign(this);
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
  Grouping(Expr expression) : _expression(expression) {}
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

  template <typename R>
  R accept(Visitor<R> visitor)
  {
    return visitor.visitVariableExpr(this);
  }

  Token _name;
};

template <typename R>
class Visitor
{
  virtual R visitAssignExpr(Assign expr);
  virtual R visitBinaryExpr(Binary expr);
  virtual R visitCallExpr(Call expr);
  virtual R visitGetExpr(Get expr);
  virtual R visitGroupingExpr(Grouping expr);
  virtual R visitLiteralExpr(Literal expr);
  virtual R visitLogicalExpr(Logical expr);
  virtual R visitSetExpr(Set expr);
  virtual R visitSuperExpr(Supevirtual r expr);
  virtual R visitThisExpr(This expr);
  virtual R visitUnaryExpr(Unary expr);
  virtual R visitVariableExpr(Variable expr);
};
}; // namespace Decl

#endif