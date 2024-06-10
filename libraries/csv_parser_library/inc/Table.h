#pragma once

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include <cstdlib>
#include <iomanip>

using namespace std; //переписать на std

class Table
{
public:
	Table(const vector<string>& keys, const  vector<vector<string>>& data);//We accept keys - column names and data
	
	void evaluate_formulas();//Finding a formula in a cell 

	void display() const;

private:
	void evaluate_formula(pair< string, vector<string >> item);

	void evaluate_addition(string& cell, int& count_vector, pair< string, vector<string >>& item);

	void evaluate_subtraction(string& cell, int& count_vector, pair< string, vector<string >>& item);

	void evaluate_multiplication(string& cell, int& count_vector, pair< string, vector<string >>& item);

	void evaluate_division(string& cell, int& count_vector, pair< string, vector<string >>& item);

	void evaluate_sin(string& cell, int& count_vector, pair< string, vector<string >>& item);

	void evaluate_cos(string& cell, int& count_vector, pair< string, vector<string >>& item);

	int writing_variable(const string& expression);

	pair<int, int> writing_variables( char symbol_operation, const string& expression);

	map<string, vector<string>> m;
};


