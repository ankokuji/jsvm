#ifndef LOCAL_VALUE
#define LOCAL_VALUE

#include <string>

using std::string;

typedef int integer;

namespace Value
{
class Value
{
  virtual bool IsString()
  {
    return false;
  };
};

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