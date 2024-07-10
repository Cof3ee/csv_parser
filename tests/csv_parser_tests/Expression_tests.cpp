#include "gtest/gtest.h"
#include "Expression.h"

using namespace std;

TEST(Expression, evaluate_expression_test_addition_calculated)
{
	pair <string, vector <string>> test;
	pair <string, vector <string>> original;

	test.first = "A";
	test.second = { "1+2" };

	original.first = "A";
	original.second = { "3.000000" };


	Expression ex;
	pair <int, double> result_expression = ex.evaluate_expression(test);

	test.second[result_expression.first] = to_string(result_expression.second);

  ASSERT_EQ(test, original);
}

TEST(Expression, evaluate_expression_test_subtraction_calculated)
{
	pair <string, vector <string>> test;
	pair <string, vector <string>> original;

	test.first = "A";
	test.second = { "4-2" };

	original.first = "A";
	original.second = { "2.000000" };


	Expression ex;
	pair <int, double> result_expression = ex.evaluate_expression(test);

	test.second[result_expression.first] = to_string(result_expression.second);

	ASSERT_EQ(test, original);
}

TEST(Expression, evaluate_expression_test_division_calculated)
{
	pair <string, vector <string>> test;
	pair <string, vector <string>> original;

	test.first = "A";
	test.second = { "4/2" };

	original.first = "A";
	original.second = { "2.000000" };


	Expression ex;
	pair <int, double> result_expression = ex.evaluate_expression(test);

	test.second[result_expression.first] = to_string(result_expression.second);

	ASSERT_EQ(test, original);
}

TEST(Expression, evaluate_expression_test_multiplication_calculated)
{
	pair <string, vector <string>> test;
	pair <string, vector <string>> original;

	test.first = "A";
	test.second = { "1*2" };

	original.first = "A";
	original.second = { "2.000000" };


	Expression ex;
	pair <int, double> result_expression = ex.evaluate_expression(test);

	test.second[result_expression.first] = to_string(result_expression.second);

	ASSERT_EQ(test, original);
}

TEST(Expression, evaluate_expression_test_three_operands)
{
	pair <string, vector <string>> test;
	pair <string, vector <string>> original;

	test.first = "A";
	test.second = { "1+2-1" };

	original.first = "A";
	original.second = { "2.000000" };


	Expression ex;
	pair <int, double> result_expression = ex.evaluate_expression(test);

	test.second[result_expression.first] = to_string(result_expression.second);

	ASSERT_EQ(test, original);
}

TEST(Expression, evaluate_expression_test_four_operands)
{
	pair <string, vector <string>> test;
	pair <string, vector <string>> original;

	test.first = "A";
	test.second = { "1+2-1+1" };

	original.first = "A";
	original.second = { "3.000000" };


	Expression ex;
	pair <int, double> result_expression = ex.evaluate_expression(test);

	test.second[result_expression.first] = to_string(result_expression.second);

	ASSERT_EQ(test, original);
}

TEST(Expression, evaluate_expression_test_priority_operations)
{
	pair <string, vector <string>> test;
	pair <string, vector <string>> original;

	test.first = "B";
	test.second = { "2*2-2/2" };

	original.first = "B";
	original.second = { "3.000000" };


	Expression ex;
	pair <int, double> result_expression = ex.evaluate_expression(test);

	test.second[result_expression.first] = to_string(result_expression.second);

	ASSERT_EQ(test, original);
}

TEST(Expression, Expression_evaluate_expression_test_division_by_zero)
{
	pair <string, vector <string>> test;
	test.first = "A";
	test.second = { "2/0" };

	Expression ex;
	
	ASSERT_THROW(ex.evaluate_expression(test), runtime_error);
}

TEST(Expression, Expression_evaluate_expression_test_any_exception)
{
	pair <string, vector <string>> test;
	
	test.first = "A";
	test.second = { "242*2-5/2","134*2+2-5-6+2+1+3"};

	Expression ex;
	
	ASSERT_NO_THROW(ex.evaluate_expression(test));
}