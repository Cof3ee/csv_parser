#pragma once
#include "Table.h"
#include "CsvParserException.h"
#include <string>	
#include <vector>

class Expression 
{
public:
	std::pair<int, double> evaluate_expression(const std::pair< std::string, std::vector<std::string >>& item); 

private:
	double calculate_arithmetic_expression(const std::string& tokens);

	int get_priority(const char& op) const;

	bool is_operator(const char& c) const;
};