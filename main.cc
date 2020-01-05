
#include "AstPrinter.h"
#include "Expr.h"

int main(int argc, char *argv[])
{

  AstPrinter printer;

  Expr::Expr ee = Expr::Literal(53.326);

  Expr::Grouping se();

  Expr::Expr expression = Expr::Binary(
      Expr::Unary(
          Token(MINUS, "-", NULL, 1),
          Expr::Literal(123)),
      Token(STAR, "*", NULL, 1),
      Expr::Grouping(
          Expr::Literal(45.67)));

}