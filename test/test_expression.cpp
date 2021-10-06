#include <unity.h>
#include <expression.h>
#define eq TEST_ASSERT_EQUAL_FLOAT

Expression e;

void test_evaluate(void)
{
  eq(1, e.evaluate("1"));
}

void test_basic_ops(void)
{
  eq(2, e.evaluate("1+1"));
  eq(0, e.evaluate("1-1"));
  eq(2, e.evaluate("1*2"));
  eq(0.5, e.evaluate("1/2"));
}

void test_parens(void)
{
  eq(1.2, e.evaluate("1+(1/5)"));
  eq(30, e.evaluate("5(6)"));
  eq(90, e.evaluate("5(6)3"));

  // Closing parens are optional, like most scientific calcs
  eq(48, e.evaluate("1(2(3(4+4)"));
  eq(9, e.evaluate("3((((((3)))"));
}

void test_precedence(void)
{

  eq(5.6, e.evaluate("4+8/(9-4)"));
  eq(3, e.evaluate("1+2"));
  eq(1.75, e.evaluate("1+3/4"));
  eq(1, e.evaluate("(1+3)/4"));
  eq(12, e.evaluate("4(1)(3)"));
  eq(12, e.evaluate("4(1(3))"));
}

void process()
{
  UNITY_BEGIN();
  RUN_TEST(test_evaluate);
  RUN_TEST(test_basic_ops);
  RUN_TEST(test_parens);
  RUN_TEST(test_precedence);
  UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>
void setup()
{
  delay(5000);
  process();
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(500);
}

#else

int main(int argc, char **argv)
{
  process();
  return 0;
}

#endif
