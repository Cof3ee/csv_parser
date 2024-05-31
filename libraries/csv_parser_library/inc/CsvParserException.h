#pragma once

#include<iostream>
#include<string>

using namespace std; //���������� �� std

class CsvParserException : public exception //������� �������� �� csv_parser_exception
{
public:
	CsvParserException(char symbol, string cell);
	
	char GetSymbol();

	string GetCell();

private:
	char symbol_;
	string cell_;
};
