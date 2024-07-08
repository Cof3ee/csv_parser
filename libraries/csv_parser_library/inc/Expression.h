#pragma once
#include "Table.h"
#include "CsvParserException.h"
#include <string>
#include <vector>
#include <sstream>	//Изучить для чего нужна библиотека
#include <stack>	//Изучить для чего нужна библиотека
#include <cctype>	//Изучить для чего нужна библиотека

/* 
*
Формула evaluate formula делает проверку в выражении типа pair <string, vector<string>
Когда находит это выражение, передаёт эту пару, далее ищется именно вектор где написано это выражение и вызывается уже саммая нужнуя функция
В которую передаётся vector<string> 
Далее мы уже работаем с этим вектором и возвращаем посчитанное значение этого выражения
Затем нужно будет заменить математическое выражение в ячейке

*/
class Expression 
{
public:
	std::pair<int, double> evaluate_expression(const std::pair< std::string, std::vector<std::string >>& item); 

private:
	double calculate_arithmetic_expression(const std::string& tokens);

	int getPriority(const char& op) const;

	bool isOperator(const char& c) const;
};