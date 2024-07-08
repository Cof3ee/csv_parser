#include "Expression.h"

using namespace std;

pair<int,double> Expression::evaluate_expression(const pair< string, vector<string >> & item) 
{
	char addition = '+';
	char subtraction = '-';
	char multiplication = '*';
	char division = '/';
    int counter_vector = 0;

	for (auto cell : item.second) //Extract cell from vector
	{
		for (char symbol : cell)
		{
			if (symbol == '=')
			{
				break;
			}
			else if (symbol == addition || symbol == subtraction || symbol == multiplication || symbol == division)
			{
                double result_expression = calculate_arithmetic_expression(cell);
                
                pair <int, double> result;
                result.first = counter_vector;
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
        // Пропускаем пробелы
        if (isspace(expression[i]))
        {
            continue;
        }

        // Если символ - цифра, то добавляем ее в стек операндов
        if (isdigit(expression[i]))
        {
            int num = 0;

            while (i < expression.length() && isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--; // Возвращаемся на один шаг назад, чтобы не пропустить символ
            operands.push(num);
        }

        // Если символ - оператор, то обрабатываем его
        if (isOperator(expression[i]))
        {
            // Если в стеке операторов уже есть оператор с более высоким приоритетом,
            // то вычисляем предыдущее выражение
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(expression[i]))
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

    // Вычисляем оставшиеся выражения в стеке
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

// Функция для проверки, является ли символ оператором
bool Expression::isOperator(const char& c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Функция для определения приоритета оператора
int Expression::getPriority(const char& op) const
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
