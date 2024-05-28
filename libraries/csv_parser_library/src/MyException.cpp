#include "MyException.h"

MyException:: MyException(char symbol, string cell)
{
	symbol_ = symbol;
	cell_ = cell;
}

char MyException::GetSymbol()
{
	return symbol_;
}

string MyException::GetCell()
{
	return cell_;
}

