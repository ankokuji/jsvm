#ifndef AST_PRINTER
#define AST_PRINTER

#include "Expr.h"
#include "Value.h"
#include <string>

using std::string;

typedef Value::String *val_str_ptr;

val_str_ptr fromString(string str) {
  return Value::String::New(str);
}

class AstPrinter : public Expr::Visitor
{
public:
  val_str_ptr visitBinaryExpr(Expr::Binary expr) override
  {
    string str = parenthesize(expr._op._lexeme, {expr._left, expr._right});
    return fromString(str);
  }

  val_str_ptr visitGroupingExpr(Expr::Grouping expr) override
  {
    return fromString(parenthesize("group", {expr._expression}));
  }

  template <typename T>
  val_str_ptr visitLiteralExpr(Expr::Literal<T> expr) override
  {
    if (expr._value == NULL)
      return "null";
    return expr._value;
  }

  val_str_ptr visitUnaryExpr(Expr::Unary expr) override
  {
    return fromString(parenthesize(expr._op._lexeme, {expr._right}));
  }

private:
  string parenthesize(string name, vector<Expr::Expr> right)
  {
    // StringBuilder builder = new StringBuilder();

    // builder.append("(").append(name);
    // for (Expr expr : exprs)
    // {
    //   builder.append(" ");
    //   builder.append(expr.accept(this));
    // }
    // builder.append(")");

    // return builder.toString();

    vector<string> builder;
    builder.push_back("(");
    builder.push_back(name);
    for (auto it = right.cbegin(); it != right.cend(); it++)
    {
      builder.push_back(" ");
      builder.push_back("");
    }

    builder.push_back(")");
    return "ab";
  }
};

#endif