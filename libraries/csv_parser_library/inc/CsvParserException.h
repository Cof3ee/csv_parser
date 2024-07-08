#pragma once

#include<iostream>
#include<string>

class CsvParserException : public std::exception 
{
public:
	CsvParserException(char symbol, const std::string & cell);

	/*CsvParserException(const std::string& cell);*/
	
	char GetSymbol();

	std::string GetCell();

private:
	char symbol_;
	std::string cell_;
};
