#pragma once

#include<iostream>
#include<string>

class CsvParserException : public std::exception 
{
public:
	CsvParserException(char symbol, std::string cell);
	
	char GetSymbol();

	std::string GetCell();

private:
	char symbol_;
	std::string cell_;
};
