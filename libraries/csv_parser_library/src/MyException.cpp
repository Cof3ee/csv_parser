#include "MyException.h"

CsvParserException:: CsvParserException(char symbol, string cell)
{
	symbol_ = symbol;
	cell_ = cell;
}

char CsvParserException::GetSymbol()
{
	return symbol_;
}

string CsvParserException::GetCell()
{
	return cell_;
}

