#pragma once

#include<iostream>
#include<string>

using namespace std;

class MyException : public exception
{
public:
	MyException(char symbol, string cell);
	
	char GetSymbol();

	string GetCell();

private:
	char symbol_;
	string cell_;
};
