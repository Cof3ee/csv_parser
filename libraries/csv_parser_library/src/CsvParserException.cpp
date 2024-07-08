#include "CsvParserException.h"

using namespace std;

CsvParserException:: CsvParserException(char symbol, const string& cell) : symbol_ (symbol), cell_ (cell)
{}

//CsvParserException::CsvParserException(const std::string & cell) : cell_(cell)
//{}

char CsvParserException::GetSymbol()
{
	return symbol_;
}

string CsvParserException::GetCell()
{
	return cell_;
}

