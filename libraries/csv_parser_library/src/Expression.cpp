#include "Expression.h"
#include <sstream>	
#include <stack>	
#include <cctype>

using namespace std;

pair<int,double> Expression::evaluate_expression(const pair< string, vector<string >> & item) 
{
    int counter_vector = 0;

	for (auto cell : item.second) //Extract cell from vector
	{
		for (char symbol : cell)
		{
			if (symbol == '=')
			{
				break;
			}
			else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/')
			{
                double result_expression = calculate_arithmetic_expression(cell);
                
                pair <int, double> result;
                result.first = counter_vector; //Serial number of a formula in vector
                result.second = result_expression; 

                return result;
			}
		}
        counter_vector++;
	}
}

double Expression::calculate_arithmetic_expression(const string& expression)
{   
    stack<int> operands;
    stack<char> operators;

    for (int i = 0; i < expression.length(); i++)
    {
        // Skip spaces
        if (isspace(expression[i]))
        {
            continue;
        }

        // If the character is a digit, then add it to the operand stack
        if (isdigit(expression[i]))
        {
            int num = 0;

            while (i < expression.length() && isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--; // Go back one step so as not to miss a character
            operands.push(num);
        }

        // If the symbol is an operator, then we process it
        if (is_operator(expression[i]))
        {
            // If there is already a higher priority operator in the operator stack,
            // then we evaluate the previous expression
            while (!operators.empty() && get_priority(operators.top()) >= get_priority(expression[i]))
            {
                int operand2 = operands.top();
                operands.pop();
                int operand1 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();

                switch (op) 
                {
                case '+':
                    operands.push(operand1 + operand2);
                    break;
                case '-':
                    operands.push(operand1 - operand2);
                    break;
                case '*':
                    operands.push(operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) 
                    {
                        throw runtime_error("Division by zero!");
                    }
                    operands.push(operand1 / operand2);
                    break;
                }
            }
            operators.push(expression[i]);
        }
    }

    // Evaluating the remaining expressions on the stack
    while (!operators.empty())
    {
        int operand2 = operands.top();
        operands.pop();
        int operand1 = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();

        switch (op) 
        {
        case '+':
            operands.push(operand1 + operand2);
            break;
        case '-':
            operands.push(operand1 - operand2);
            break;
        case '*':
            operands.push(operand1 * operand2);
            break;
        case '/':
            if (operand2 == 0) 
            {
                throw runtime_error("Division by zero!");
            }
            operands.push(operand1 / operand2);
            break;
        }
    }

    return operands.top();
}

// Function to check if a symbol is an operator
bool Expression::is_operator(const char& c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function for determining operator priority
int Expression::get_priority(const char& op) const
{
    if (op == '*' || op == '/')
    {
        return 2;
    }
    else if (op == '+' || op == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}