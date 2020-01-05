#ifndef AST_PRINTER
#define AST_PRINTER

#include "Expr.h"
#include <string>

using std::string;

class AstPrinter : public Decl::Visitor<string>
{
public:
  string visitBinaryExpr(Decl::Binary expr) override
  {
    return parenthesize(expr._op._lexeme, {expr._left, expr._right});
  }

  string visitGroupingExpr(Decl::Grouping expr) override
  {
    return parenthesize("group", {expr._expression});
  }

  template <typename T>
  string visitLiteralExpr(Decl::Literal<T> expr) override
  {
    if (expr.value == NULL)
      return "nil";
    return expr.value.tostring();
  }

  string visitUnaryExpr(Decl::Unary expr) override
  {
    return parenthesize(expr._op._lexeme, {expr._right});
  }

  string parenthesize(string name, vector<Decl::Expr> right)
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