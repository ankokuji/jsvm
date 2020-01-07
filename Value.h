#ifndef LOCAL_VALUE
#define LOCAL_VALUE

#include <string>
#include "Function.h"

using std::string;

typedef int integer;
typedef Function js_function;

namespace Value
{
class Value
{
  virtual bool IsString()
  {
    return false;
  };
};

class Function : public Value
{
public:
  static Function *New(js_function &func)
  {
    return Function(func);
  }

private:
  Function(js_function &func) : _val(func){};
  js_function _val;
}

class Integer : public Value
{

public:
  static Integer *New(integer i)
  {
    return new Integer(i);
  };

  integer Value()
  {
    return _val;
  }

private:
  Integer(integer i) : _val(i){};
  integer _val;
};

class String : public Value
{

public:
  static String *New(string i)
  {
    return new String(i);
  };

  String Value()
  {
    return _val;
  }

private:
  String(string i) : _val(i){};
  string _val;
};

class Double
{
};
}; // namespace Value

#endif