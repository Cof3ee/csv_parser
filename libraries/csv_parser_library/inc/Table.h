#pragma once

#include "CsvParserException.h"
#include "Expression.h"
#include <map>
#include <vector>
#include <string>
#include <cstdlib>

class Table
{
public:
	Table(const std::vector<std::string>& keys, const  std::vector<std::vector<std::string>>& data);//We accept keys - column names and data
	
	void evaluate_formulas();//Finding a formula in a cell 

	void display() const;

	bool operator == (const Table& other) const;

private:
	void evaluate_formula(std::pair<std::string, std::vector<std::string >> item);

	void evaluate_addition(std::string& cell, int& count_vector, std::pair< std::string, std::vector<std::string >>& item);

	void evaluate_subtraction(std::string& cell, int& count_vector, std::pair< std::string, std::vector<std::string >>& item);

	void evaluate_multiplication(std::string& cell, int& count_vector, std::pair< std::string, std::vector<std::string >>& item);

	void evaluate_division(std::string& cell, int& count_vector, std::pair< std::string, std::vector<std::string >>& item);

	void evaluate_sin(std::string& cell, int& count_vector, std::pair< std::string, std::vector<std::string >>& item);

	void evaluate_cos(std::string& cell, int& count_vector, std::pair< std::string, std::vector<std::string >>& item);

	int writing_variable(const std::string& expression);

	std::pair<int, int> writing_variables( const char& symbol_operation, const std::string& expression);

	void evaluate_expression(std::pair< std::string, std::vector<std::string >> item);

private:
	std::map<std::string, std::vector<std::string>> m;
};