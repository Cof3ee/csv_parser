#include "Table.h"

Table::Table(const vector<string>& keys, const  vector<vector<string>>& data) //We accept keys - column names and data
{
	//Variable for iteration over keys
	int counter = 0;

	for (const vector<string>& values : data) //Recording your own data for columns
	{
		m.emplace(keys[counter++], values);
	}
}

//Finding a formula in a cell 
void Table::evaluate_formulas()
{
	for (const auto& column : m) //Pull a pair from the map
	{
		for (auto cell : column.second) //Extract cell from vector
		{
			for (char symbol : cell) //Search for a formula that starts with: "="
			{
				if (symbol == '=')
				{
					try
					{
						evaluate_formula(column); //If the formula is found, then the function is called to search for the operation symbol
				    }
					catch (exception& ex)
					{
						cout << ex.what() << endl;
					}
				}
				break;
			}
		}
	}
}

//Displaying a table on the screen
void Table:: display() const
{
	for (const auto& column : m) //Displaying column names
	{
		cout << column.first << '\t';
	}

	cout << endl;

	for (size_t counter = 0; counter < m.size(); counter++) //Output of other data
	{
		for (const auto& pair : m) //Extracting a pair
		{
			if (counter < pair.second.size()) //If the counter does not exceed the size of vector
			{
				cout << pair.second[counter] << '\t';
			}
		}
		cout << endl;
	}
}

//Search for the symbol of the mate operation
void Table::evaluate_formula(pair< string, vector<string >> item)
{
	int a=0;
	for (auto cell : item.second) //Extract cell from vector
	{
		for (char symbol : cell) //Search for mat symbol. operations
		{ 
			    if (symbol == '+')
			    {
				  evaluate_plus(item);
				  a++;
			    }
			   if (symbol == '-')
			   {
				  evaluate_minus(item);
				  a++;
			   }
			   if (symbol == '*')
			   {
				  evaluate_multiplication(item);
				  a++;
			   }
			   if (symbol == '/')
			   {
				  evaluate_segmentation(item);
				  a++;
			   }
		    
		}
	}
	if (a < 1)
	{
		throw exception("The operation symbol was entered incorrectly!");
	}
}

//Calculating the amount
void Table::evaluate_plus(pair< string, vector<string >> item)
{
	//Counter to indicate the cell in which the formula
	int count_vector = 0;

	for (auto cell : item.second) //Extract cell from vector
	{
		for (char symbol : cell) //Search for formula
		{
			if (symbol == '=')
			{
				//Calling a function to search for variables and calculate the result
				int result = writing_variables('+', cell).first + writing_variables('+', cell).second;

				//Writing new data to a cell
				m[item.first][count_vector] = to_string(result);
			}
			break; //To avoid iterating over the entire cell
		}
		count_vector++;
	}
}

//Calculating the difference
void Table:: evaluate_minus(pair< string, vector<string >> item)
{
	//Counter to indicate the cell in which the formula
	int count_vector = 0;

	for (auto cell : item.second) //Extract cell from vector
	{
		for (char symbol : cell) //Search for formula
		{
			if (symbol == '=')
			{
				//Calling a function to search for variables and calculate the result
				int result = writing_variables('-', cell).first - writing_variables('-', cell).second;

				//Writing new data to a cell
				m[item.first][count_vector] = to_string(result);
			}
			break; //To avoid iterating over the entire cell
		}
		count_vector++;
	}
}

//Product calculation
void Table:: evaluate_multiplication(pair< string, vector<string >> item)
{
	//Counter to indicate the cell in which the formula
	int count_vector = 0;

	for (auto cell : item.second) //Extract cell from vector
	{
		for (char symbol : cell) //Search for formula
		{
			if (symbol == '=')
			{
				//Calling a function to search for variables and calculate the result
				int result = writing_variables('*', cell).first * writing_variables('*', cell).second;

				//Writing new data to a cell
				m[item.first][count_vector] = to_string(result);
			}
			break; //To avoid iterating over the entire cell
		}
		count_vector++;
	}
}

//Counting divisions
void Table:: evaluate_segmentation(pair< string, vector<string >> item)
{
	//Counter to indicate the cell in which the formula
	int count_vector = 0;

	for (auto cell : item.second) //Extract cell from vector
	{
		for (char symbol : cell) //Search for formula
		{
			if (symbol == '=')
			{
				//Calling a function to search for variables and calculate the result
				int result = writing_variables('/', cell).first / writing_variables('/', cell).second;

				//Writing new data to a cell
				m[item.first][count_vector] = to_string(result);
			}
			break; //To avoid iterating over the entire cell
		}
		count_vector++;
	}
}
//Finding and returning variables
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

	//Writing values ??to variables that need to be read
	int value1 = stoi(m[first][count_first - 2]);
	int value2 = stoi(m[second][count_second - 2]);


	pair<int, int> variables;
	variables.first = value1;
	variables.second = value2;

	return variables;
}