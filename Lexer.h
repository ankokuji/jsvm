#ifndef LEXER
#define LEXER

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;

enum TokenType
{
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords.
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,
  EOF_TOKEN
};

class Token
{
public:
  friend class Parser;
  TokenType _type;
  string _lexeme;
  int _line;
  void *_literal;
  Token(TokenType type, string lexeme, void *literal, int line)
      : _type(type), _lexeme(lexeme), _literal(literal), _line(line){};
  string toString();
};

class Scanner
{
private:
  int start = 0;
  int current = 0;
  int line = 1;
  string source;
  vector<Token *> tokens;
  Scanner(string source);
  char advance();
  void addToken(TokenType type);
  void addToken(TokenType type, void *literal);
  bool match(char expected);
  void scanToken();

public:
  vector<Token *> scanTokens()
  {
    while (!isAtEnd())
    {
      // We are at the beginning of the next lexeme.
      start = current;
      scanTokens();
    }
    tokens.push_back(new Token(EOF_TOKEN, "", nullptr, line));
    return tokens;
  };

  bool isAtEnd()
  {
    return current >= source.length();
  }
};

#endif
