#pragma once

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include <cstdlib>

using namespace std;

class Table
{
public:
	Table(const vector<string>& keys, const  vector<vector<string>>& data);//We accept keys - column names and data
	
	void evaluate_formulas();//Finding a formula in a cell 

	void display() const;

private:
	void evaluate_formula(pair< string, vector<string >> item);

	void evaluate_addition(pair< string, vector<string >> item);

	void evaluate_subtraction(pair< string, vector<string >> item);

	void evaluate_multiplication(pair< string, vector<string >> item);

	void evaluate_division(pair< string, vector<string >> item);

	pair<int, int> writing_variables( char symbol_operation, const string& expression);

	map<string, vector<string>> m;
};

class MyExceptioin : public exception
{
public:
	MyExceptioin(char symbol,string cell)
	{
		symbol_ = symbol;
		cell_=cell;
	}
	char GetSymbol()
	{
		return symbol_;
	}
	string GetCell()
	{
		return cell_;
	}
private:
	char symbol_;
	string cell_;
};

