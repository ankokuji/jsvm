
#include "AstPrinter.h"
#include "Expr.h"

int main(int argc, char *argv[])
{

  AstPrinter printer;

  Decl::Expr ee = Decl::Literal(53.326);

  Decl::Grouping se();

  Decl::Expr expression = Decl::Binary(
      Decl::Unary(
          Token(MINUS, "-", NULL, 1),
          Decl::Literal(123)),
      Token(STAR, "*", NULL, 1),
      Decl::Grouping(
          Decl::Literal(45.67)));

}