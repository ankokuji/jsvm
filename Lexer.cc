#include "./Lexer.h"

string Token::toString()
{

  return _type + " " + _lexeme + " " + *static_cast<string *>(_literal);
}

Scanner::Scanner(string _source) : source(_source){};

char Scanner::advance()
{
  current++;
  return source[current - 1];
}

void Scanner::addToken(TokenType type)
{
  addToken(type, NULL);
}
void Scanner::addToken(TokenType type, void* literal)
{
  string text = source.substr(start, current);
  tokens.push_back(new Token(type, text, nullptr, line));
}

bool Scanner::match(char expected)
  {
    if (isAtEnd())
      return false;
    if (source[current] != expected)
      return false;
    current++;
    return true;
  }

void Scanner::scanToken()
{
  char c = advance();
  switch (c)
  {
  case '(':
    addToken(LEFT_PAREN);
    break;
  case ')':
    addToken(RIGHT_PAREN);
    break;
  case '{':
    addToken(LEFT_BRACE);
    break;
  case '}':
    addToken(RIGHT_BRACE);
    break;
  case ',':
    addToken(COMMA);
    break;
  case '.':
    addToken(DOT);
    break;
  case '-':
    addToken(MINUS);
    break;
  case '+':
    addToken(PLUS);
    break;
  case ';':
    addToken(SEMICOLON);
    break;
  case '*':
    addToken(STAR);
    break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG);
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL);
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS);
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER);
    break;
  }
}
