#ifndef PARSER
#define PARSER

#include <string>
#include <vector>
#include <stdexcept>
#include "Lexer.h"
#include "Expr.h"
#include "Stmt.h"

using std::vector;

class Parser
{
private:
  vector<Token> tokens;
  int current = 0;
  Stmt::Stmt statement() {                  
    if (match({PRINT})) return printStatement();
    return expressionStatement();             
  }

  Expr::Expr expression()
  {
    return equality();
  }

  Expr::Expr equality()
  {
    Expr::Expr expr = comparison();

    while (match({BANG_EQUAL, EQUAL_EQUAL}))
    {
      Token op = previous();
      Expr::Expr right = comparison();
      expr = Expr::Binary(expr, op, right);
    }

    return expr;
  }

  bool match(vector<TokenType> types)
  {

    std::vector<TokenType>::const_iterator begin = types.cbegin();
    std::vector<TokenType>::const_iterator end = types.cend();

    while (begin != end)
    {
      if (check(*begin))
      {
        advance();
        return true;
      }
      ++begin;
    }
    return false;
  }

  Expr::Expr comparison()
  {
    Expr::Expr expr = addition();

    while (match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL}))
    {
      Token op = previous();
      Expr::Expr right = addition();
      expr = Expr::Binary(expr, op, right);
    }

    return expr;
  }

  Expr::Expr addition()
  {
    Expr::Expr expr = multiplication();

    while (match({MINUS, PLUS}))
    {
      Token op = previous();
      Expr::Expr right = multiplication();
      expr = Expr::Binary(expr, op, right);
    }

    return expr;
  }

  Expr::Expr multiplication()
  {
    Expr::Expr expr = unary();

    while (match({SLASH, STAR}))
    {
      Token op = previous();
      Expr::Expr right = unary();
      expr = Expr::Binary(expr, op, right);
    }

    return expr;
  }

  bool check(TokenType type)
  {
    if (isAtEnd())
      return false;
    return peek()._type == type;
  }

  Expr::Expr unary()
  {
    if (match({BANG, MINUS}))
    {
      Token op = previous();
      Expr::Expr right = unary();
      return Expr::Unary(op, right);
    }
    return primary();
  }

  Expr::Expr primary()
  {
    if (match({FALSE}))
      return Expr::Literal(false);
    if (match({TRUE}))
      return Expr::Literal(true);
    if (match({NIL}))
      return Expr::Literal(NULL);

    if (match({NUMBER, STRING}))
    {
      return Expr::Literal(previous()._literal);
    }

    if (match({LEFT_PAREN}))
    {
      Expr::Expr expr = expression();
      consume(RIGHT_PAREN, "Expect ')' after expression.");
      return Expr::Grouping(expr);
    }

    throw error(peek(), "Expect expression.");
  }

  Token consume(TokenType type, std::string message)
  {
    if (check(type))
      return advance();

    throw error(peek(), message);
  }

  std::exception error(Token token, string msg)
  {
    return std::runtime_error(msg);
  }

  void synchronize()
  {
    advance();
    while (!isAtEnd())
    {
      if (previous()._type == SEMICOLON)
        return;
      switch (peek()._type)
      {
      case CLASS:
      case FUN:
      case VAR:
      case FOR:
      case IF:
      case WHILE:
      case PRINT:
      case RETURN:
        return;
      }
      advance();
    }
  }

  Token advance()
  {
    if (!isAtEnd())
      current++;
    return previous();
  }

  bool isAtEnd()
  {
    return peek()._type == EOF_TOKEN;
  }

  Token peek()
  {
    return tokens[current];
  }

  Token previous()
  {
    return tokens[current - 1];
  }

public:
  Parser(vector<Token> tokens)
  {
    tokens = tokens;
  }

  Expr::Expr parser()
  {
    return expression();
  }
};

#endif