#include "Table.h"
#include "CsvParserException.h"

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
					catch (CsvParserException& ex)
					{
						cout << "Incorrectly entered operation operator: " ;
						cout << ex.GetSymbol() << " in cell: " << ex.GetCell() << endl;
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

//Search for the symbol of the mate operation
void Table::evaluate_formula(pair< string, vector<string >> item)
{
	string searhCOS = "COS(";
	string searhSIN = "SIN(";

	int count_vector = 0;//Counter to indicate the cell in which the formula
	
	for (auto cell : item.second) //Extract cell from vector
	{
		char arrFunction[3]; //массив для проверки является ли слово "sin"/cos
		int counterFuncttion=0; //счётчик для функция cos/sin
		
		for (char symbol : cell) //Search for mat symbol. operations
		{
			if (!isdigit(symbol) && symbol!='(' && symbol!=')') //проблема здесь в том, что если в операцию неверно введена скобка, то это неверно обрабатывается
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
					size_t foundCos = cell.find(searhCOS); //ищем слово cos
					size_t foundSin = cell.find(searhSIN);

					if (foundCos != string::npos) //проверяем нашли ли
					{
						size_t start = foundCos + searhCOS.size();
						size_t end = cell.find(")", start);

						if (end != string::npos) //проверяем есть ли закрывающая скобка 
						{
							evaluate_cos(cell, count_vector, item); //если нашли и всё хорошо, то вызываем функцию
						}
						else
						{
							cout << "Eror, not found: ')' !!!"; //переписать на exception
						}
						}
					else if (foundSin != string::npos)
					{
						size_t start = foundSin + searhSIN.size();
						size_t end = cell.find(")", start);

						if (end != string::npos)
						{
							evaluate_sin(cell, count_vector, item);
						}
						else
						{
							cout << "Eror, not found: ')' !!!"; //переписать на exception
						}
					}
				}
					//else if (symbol == 'S' || symbol == 'I' || symbol == 'N')
					//{
					// arrFunction[counterFuncttion++] = symbol; //по очереди записываем название функции
					//	if (counterFuncttion == 3) //если 3 буквы в массиве
					//	{
					//		if (arrFunction[0] == 'S' && arrFunction[1] == 'I' && arrFunction[2] == 'N') //проверяем слово
					//		{
					//			evaluate_sin(cell, count_vector, item); //если всё норм, то считаем
					//		}
					//	}
					//}
					//else if (symbol == 'C' || symbol == 'O' || symbol == 'S')
					//{
					//	arrFunction[counterFuncttion++] = symbol; //по очереди записываем название функции
					//	if (counterFuncttion == 3) //если 3 буквы в массиве
					//	{
					//		if (arrFunction[0] == 'C' && arrFunction[1] == 'O' && arrFunction[2] == 'S') //проверяем слово
					//		{
					//			evaluate_cos(cell, count_vector, item); //если всё норм, то считаем
					//		}
					//	}
				    //} //как проверял сначала, но обнаружилось что и в cos и sin есть s :)
			}
		}
		count_vector++;
	}
}

//Calculating the amount
void Table::evaluate_addition(string &cell, int &count_vector, pair< string, vector<string >>& item)
{
	//Calling a function to search for variables and calculate the result
	int result = writing_variables('+', cell).first + writing_variables('+', cell).second;

	//Writing new data to a cell
	m[item.first][count_vector] = to_string(result);
}

//Calculating the difference
void Table::evaluate_subtraction(string& cell, int& count_vector, pair< string, vector<string >>& item)
{
	//Calling a function to search for variables and calculate the result
	int result = writing_variables('-', cell).first - writing_variables('-', cell).second;

	//Writing new data to a cell
	m[item.first][count_vector] = to_string(result);
}

//Product calculation
void Table:: evaluate_multiplication(string& cell, int& count_vector, pair< string, vector<string >>& item)
{
	//Calling a function to search for variables and calculate the result
	int result = writing_variables('*', cell).first * writing_variables('*', cell).second;

	//Writing new data to a cell
	m[item.first][count_vector] = to_string(result);
}

//Counting divisions
void Table::evaluate_division(string& cell, int& count_vector, pair< string, vector<string >>& item)
{
	//Calling a function to search for variables and calculate the result
	int result = writing_variables('/', cell).first / writing_variables('/', cell).second;

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
	size_t expression_start_position = expression.find('(');

	string cell_expression = expression.substr(expression_start_position+1);
	cell_expression.pop_back();

	char digitChar = cell_expression.back();

	int count = digitChar - '0';

	cell_expression.pop_back();
	
	int value = stoi(m[cell_expression][count - 2]);

	return value;
}
//****не забыть проверить на exception после финального написани



pair<int, int> Table:: writing_variables(char symbol_operation, const string& expression)
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