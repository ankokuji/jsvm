#ifndef PARSER
#define PARSER

#include <string>
#include <vector>
#include <stdexcept>
#include "Lexer.h"
#include "Expr.h"

using std::vector;

class Parser
{
private:
  vector<Token> tokens;
  int current = 0;


  Stmt statement() {                  
    if (match({PRINT})) return printStatement();

    return expressionStatement();             
  }   

  Decl::Expr expression()
  {
    return equality();
  }

  Decl::Expr equality()
  {
    Decl::Expr expr = comparison();

    while (match({BANG_EQUAL, EQUAL_EQUAL}))
    {
      Token op = previous();
      Decl::Expr right = comparison();
      expr = Decl::Binary(expr, op, right);
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

  Decl::Expr comparison()
  {
    Decl::Expr expr = addition();

    while (match({GREATER, GREATER_EQUAL, LESS, LESS_EQUAL}))
    {
      Token op = previous();
      Decl::Expr right = addition();
      expr = Decl::Binary(expr, op, right);
    }

    return expr;
  }

  Decl::Expr addition()
  {
    Decl::Expr expr = multiplication();

    while (match({MINUS, PLUS}))
    {
      Token op = previous();
      Decl::Expr right = multiplication();
      expr = Decl::Binary(expr, op, right);
    }

    return expr;
  }

  Decl::Expr multiplication()
  {
    Decl::Expr expr = unary();

    while (match({SLASH, STAR}))
    {
      Token op = previous();
      Decl::Expr right = unary();
      expr = Decl::Binary(expr, op, right);
    }

    return expr;
  }

  bool check(TokenType type)
  {
    if (isAtEnd())
      return false;
    return peek()._type == type;
  }

  Decl::Expr unary()
  {
    if (match({BANG, MINUS}))
    {
      Token op = previous();
      Decl::Expr right = unary();
      return Decl::Unary(op, right);
    }
    return primary();
  }

  Decl::Expr primary()
  {
    if (match({FALSE}))
      return Decl::Literal(false);
    if (match({TRUE}))
      return Decl::Literal(true);
    if (match({NIL}))
      return Decl::Literal(NULL);

    if (match({NUMBER, STRING}))
    {
      return Decl::Literal(previous()._literal);
    }

    if (match({LEFT_PAREN}))
    {
      Decl::Expr expr = expression();
      consume(RIGHT_PAREN, "Expect ')' after expression.");
      return Decl::Grouping(expr);
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

  Decl::Expr parser()
  {
    return expression();
  }
};

#endif