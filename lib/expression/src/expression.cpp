#include <stack>
#include <queue>
#include <iostream>
#include <expression.h>

// Evaluate `expression` using the shunting-yard algorithm
float Expression::evaluate(std::string expression)
{
  // Create a stack for operators
  std::stack<Value> operator_stack;

  // Create a queue for operands
  std::queue<Value> operand_queue;

  // Iterate over the expression string
  for (char c : expression)
  {
    if (is_operand(c))
    {
      // Create a new operand value
      Value op;
      op.type = OPERAND;
      op.data.operand = c - '0';

      // Push the operand to the queue
      operand_queue.push(op);
    }
    else if (is_operator(c))
    {
      // Create a new operator value
      Value op;
      op.type = OPERATOR;
      op.data.op = c;

      // While the stack is not empty and the top of the stack is an operator
      while (!operator_stack.empty() && precedence(operator_stack.top().data.op) >= precedence(op.data.op))
      {
        // Pop the operator from the stack and push it to the queue
        operand_queue.push(operator_stack.top());
        operator_stack.pop();
      }

      // Push the current operator to the stack
      operator_stack.push(op);
    }
    else if (c == '(')
    {
      Value op;
      op.type = OPERATOR;
      op.data.op = c;
      operator_stack.push(op);
    }
    else if (c == ')')
    {
      while (!operator_stack.empty() && operator_stack.top().data.op != '(')
      {
        operand_queue.push(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.pop();
    }
  }

  // While the stack is not empty
  while (!operator_stack.empty())
  {
    // Pop the operator from the stack and push it to the queue
    operand_queue.push(operator_stack.top());
    operator_stack.pop();
  }

  std::stack<float> result;
  while (!operand_queue.empty())
  {
    Value v = operand_queue.front();
    operand_queue.pop();

    if (v.type == OPERAND)
    {
      result.push(v.data.operand);
    }
    else
    {
      // Handle when users don't add trailing parents
      if (v.data.op == '(')
      {
        continue;
      }
      float op1 = result.top();
      result.pop();
      float op2 = result.top();
      result.pop();
      switch (v.data.op)
      {
      case '+':
        result.push(op1 + op2);
        break;
      case '-':
        result.push(op2 - op1);
        break;
      case '*':
        result.push(op1 * op2);
        break;
      case '/':
        result.push(op2 / op1);
        break;
      }
    }
  }

  while (result.size() > 1)
  {
    double op1 = result.top();
    result.pop();
    double op2 = result.top();
    result.pop();
    result.push(op1 * op2);
  }

  return result.top();
}

// Check if `c` is an operand
bool Expression::is_operand(char c)
{
  return c >= '0' && c <= '9';
}

// Check if `c` is an operator
bool Expression::is_operator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/';
}

// Check if `c1` has a higher or equal precedence to `c2`
int Expression::precedence(char op)
{
  switch (op)
  {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  default:
    return 0;
  }
}
