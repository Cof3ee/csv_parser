#pragma once
#include "Table.h"
#include "CsvParserException.h"
#include <string>
#include <vector>
#include <sstream>	//������� ��� ���� ����� ����������
#include <stack>	//������� ��� ���� ����� ����������
#include <cctype>	//������� ��� ���� ����� ����������

/* 
*
������� evaluate formula ������ �������� � ��������� ���� pair <string, vector<string>
����� ������� ��� ���������, ������� ��� ����, ����� ������ ������ ������ ��� �������� ��� ��������� � ���������� ��� ������ ������ �������
� ������� ��������� vector<string> 
����� �� ��� �������� � ���� �������� � ���������� ����������� �������� ����� ���������
����� ����� ����� �������� �������������� ��������� � ������

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