#include <string>

#ifndef EXPRESSION_H
#define EXPRESSION_H

enum Type
{
  OPERATOR,
  OPERAND
};

union Data
{
  char op;
  float operand;
};

struct Value
{
  Type type;
  Data data;
};

class Expression
{

private:
  std::string expression;

  bool is_operand(char c);
  bool is_operator(char c);
  int precedence(char op);

public:
  Expression()
  {
  }

  float evaluate(std::string expression);
};

#endif
