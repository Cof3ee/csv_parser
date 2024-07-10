#include "Table.h"
#include <iostream>
#include <iomanip>

using namespace std;

//We accept keys - column names and data
Table::Table(const vector<string>& keys, const  vector<vector<string>>& data)
{
	int counter = 0; //Variable for iteration over keys

	for (const vector<string>& values : data) //Recording your own data for columns
	{
		m.emplace(keys[counter++], values);
	}
}

//Finding formulas
void Table::evaluate_formulas()
{
	for (const auto& column : m) //Pull a pair from the map
	{
		for (auto cell : column.second) //Extract cell from vector
		{
			for (char symbol : cell) 
			{
				if (symbol == '=') //Search for a formula that starts with: "="
				{
					evaluate_formula(column);//If the formula is found, then the function is called to search for the operation symbol
					break;
				}
				else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') //Finding a formula that does not start with equal
				{
					evaluate_expression(column);
					break;
				}
			}
		}
	}
}

//Displaying a table on the screen
void Table:: display() const
{
	for (const auto& column : m) //Displaying column names
	{
		cout <<setw(10) <<column.first;
	}

	cout << endl;

	for (size_t counter = 0; counter < m.size(); counter++) //Output of other data
	{
		for (const auto& pair : m) //Extracting a pair
		{
			if (counter < pair.second.size()) //If the counter does not exceed the size of vector
			{
				cout << setw(10) << pair.second[counter];
			}
		}
		cout << endl;
	}
}

//Definition of mathematical operation
void Table::evaluate_formula(pair< string, vector<string >> item)
{
	string searhCOS = "COS(";
	string searhSIN = "SIN(";

	int count_vector = 0;//Counter to indicate the cell in which the formula
	
	for (auto cell : item.second) //Extract cell from vector
	{
		for (char symbol : cell) //Search for mat symbol. operations
		{
			if (!isdigit(symbol) && symbol!='(' && symbol!=')'&&symbol!='.')
			{
				if (!isalpha(symbol) && symbol!='=')
				{
					if (symbol == '+')
					{
						evaluate_addition(cell, count_vector, item);
					}
					else if (symbol == '-')
					{
						evaluate_subtraction(cell, count_vector,item);
					}
					else if (symbol == '*')
					{
						evaluate_multiplication(cell, count_vector, item);
					}
					else if (symbol == '/')
					{
						evaluate_division(cell, count_vector, item);
					}
					else
					{
						throw CsvParserException(symbol, cell);
					}
				}
				else if (symbol == '=')
				{
					//Looking for the name of the operation
					size_t foundCos = cell.find(searhCOS);  //cos npos 
					size_t foundSin = cell.find(searhSIN);  //sin npos

					if (foundCos != string::npos) //Examination for "COS"
					{
						size_t start = foundCos + searhCOS.size();
						size_t end = cell.find(")", start);

						if (end != string::npos) //Check if there is a closing parenthesis
						{
							evaluate_cos(cell, count_vector, item); 
						}
						else
						{
							throw CsvParserException(symbol, cell);
						}
					}
					else if (foundSin != string::npos) //Examination for "SIN"
					{
						size_t start = foundSin + searhSIN.size();
						size_t end = cell.find(")", start);

						if (end != string::npos)
						{
							evaluate_sin(cell, count_vector, item);
						}
						else
						{
							throw CsvParserException(symbol, cell);
						}
					}
				}
			}
		}
		count_vector++;
	}
}

void Table::evaluate_addition(string &cell, int &count_vector, pair< string, vector<string >>& item)
{
	//Calling a function to search for variables and calculate the result
	pair<int, int> variables = writing_variables('+', cell);
	int result = variables.first + variables.second;
	
	//Writing new data to a cell
	m[item.first][count_vector] = to_string(result);
}

void Table::evaluate_subtraction(string& cell, int& count_vector, pair< string, vector<string >>& item)
{
	//Calling a function to search for variables and calculate the result
	pair<int, int> variables = writing_variables('-', cell);
	int result = variables.first - variables.second;

	//Writing new data to a cell
	m[item.first][count_vector] = to_string(result);
}

void Table::evaluate_multiplication(string& cell, int& count_vector, pair< string, vector<string >>& item)
{
	//Calling a function to search for variables and calculate the result
	pair<int, int> variables = writing_variables('*', cell);
	int result = variables.first + variables.second;

	//Writing new data to a cell
	m[item.first][count_vector] = to_string(result);
}

void Table::evaluate_division(string& cell, int& count_vector, pair< string, vector<string >>& item)
{
	//Calling a function to search for variables and calculate the result
	pair<int, int> variables = writing_variables('/', cell);
	int result = variables.first + variables.second;

	//Writing new data to a cell
	m[item.first][count_vector] = to_string(result);
}

void Table::evaluate_sin(string& cell, int& count_vector, pair< string, vector<string >>& item)
{
	int value_sin = writing_variable(cell);
	double result = sin(value_sin);

	m[item.first][count_vector] = to_string(result);
}

void Table::evaluate_cos(string& cell, int& count_vector, pair< string, vector<string >>& item)
{
	int value_cos = writing_variable(cell);
	double result = cos(value_cos);

	m[item.first][count_vector] = to_string(result);
}

int Table::writing_variable(const string& expression)
{
	//Search for the end of the operation name
	size_t expression_start_position = expression.find('(');
	
	//Setting the desired cell for the operation
	string cell_expression = expression.substr(expression_start_position+1);
	//Removing a parenthesis
	cell_expression.pop_back();
	
	// Extracting the last character (digit)
	char digitChar = cell_expression.back();
	// Convert a digit character to a number (int)
	int count = digitChar - '0';
	// Remove the last character from a string
	cell_expression.pop_back();
	
	//Writing value to variables that need to be read
	int value = stoi(m[cell_expression][count - 2]);

	return value;
}

pair<int, int> Table:: writing_variables(const char& symbol_operation, const string& expression)
{
	// Finding the position of symbol
	size_t operation_pos = expression.find(symbol_operation);

	// Extract the first part of the string (after the "=" and before the symbol operation)
	string first = expression.substr(1, operation_pos - 1);

	// Extract the second part of the string (after the symbol operation)
	string second = expression.substr(operation_pos + 1);

	// Extracting the last character (digit)
	char first_digitChar = first.back();
	// Convert a digit character to a number (int)
	int count_first = first_digitChar - '0';
	// Remove the last character from a string
	first.pop_back();

	char second_digitChar = second.back();
	int count_second = second_digitChar - '0';
	second.pop_back();

	//Writing values to variables that need to be read
	int value1 = stoi(m[first][count_first - 2]);
	int value2 = stoi(m[second][count_second - 2]);

	pair<int, int> variables;
	variables.first = value1;
	variables.second = value2;

	return variables;
}

//Using the Expression Class
void Table::evaluate_expression(pair<string, vector<string>> item)
{
	Expression ex;
	
	pair <int, double> result = ex.evaluate_expression(item);

	m[item.first][result.first] = to_string(result.second);
}

bool Table::operator == (const Table& other) const
{
		return this->m == other.m;
}