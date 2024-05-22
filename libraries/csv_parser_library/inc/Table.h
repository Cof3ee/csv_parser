#pragma once

#include<iostream>
#include<map>
#include<vector>
#include<string>

using namespace std;

class Table
{
public:
	Table(const vector<string>& keys, const  vector<vector<string>>& data);//We accept keys - column names and data
	
	void evaluate_formulas();//Finding a formula in a cell 

	void display() const;


private:
	void evaluate_formula(pair< string, vector<string >> item);

	void evaluate_plus(pair< string, vector<string >> item);

	void evaluate_minus(pair< string, vector<string >> item);

	void evaluate_multiplication(pair< string, vector<string >> item);

	void evaluate_segmentation(pair< string, vector<string >> item);

	pair<int, int> writing_variables(const char& symbol_operation, const string& expression);

	map<string, vector<string>> m;
};

