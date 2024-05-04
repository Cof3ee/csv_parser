#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

class Table
{
public:

	Table(const vector<string>& keys, const  vector<vector<string>>& data) //We accept keys - column names and data
	{
		//Variable for iteration over keys
		int counter = 0;  

		for (const vector<string>& values : data) //Recording your own data for columns
		{
			m.emplace(keys[counter++], values); 
		}
	}

	//Finding a formula in a cell 
	void search_formul() 
	{
		for (const auto& column : m) //Pull a pair from the map
		{
			for (auto cell : column.second) //Extract cell from vector
			{
				for (char symbol : cell) //Search for a formula that starts with: "="
				{
					if (symbol == '=')
					{
						search_mat_symbol(column); //If the formula is found, then the function is called to search for the operation symbol
					}
					break;
				}
			}
		}
	}

	//Displaying a table on the screen
	void display() const
	{
		for (const auto & column : m) //Displaying column names
		{
			cout << column.first << '\t';
		}

		cout << endl;

		for (size_t counter = 0; counter < m.size(); counter++) //Output of other data
		{
			for (const auto& pair : m) //Extracting a pair
			{
				if(counter <pair.second.size()) //If the counter does not exceed the size of vector
				{
				  cout << pair.second[counter] << '\t'; 
			    }
			}
			cout << endl;
		}
	}

private:

	//Search for the symbol of the mate operation
	void search_mat_symbol(pair< string, vector<string >> item)
	{
		for (auto cell : item.second) //Extract cell from vector
		{
			for (char symbol : cell) //Search for mat symbol. operations
			{
				if (symbol == '+')
				{
					evaluate_plus(item);
				}
				if (symbol == '-')
				{
					evaluate_minus(item);
				}
				if (symbol == '*')
				{
					evaluate_multiplication(item);
				}
				if (symbol == '/')
				{
					evaluate_segmentation(item);
				}
			}
		}
	}

	//Calculating the amount
	void evaluate_plus(pair< string, vector<string >> item)
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
					int result = writing_variables('+', cell).first+ writing_variables('+', cell).second;
					
					//Writing new data to a cell
					m[item.first][count_vector] = to_string(result);
				}
				break; //To avoid iterating over the entire cell
			}
			count_vector++; 
		}
	}
	//Calculating the difference
	void evaluate_minus(pair< string, vector<string >> item)
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
	void evaluate_multiplication(pair< string, vector<string >> item)
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
	void evaluate_segmentation(pair< string, vector<string >> item)
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
	
	pair<int, int> writing_variables(const char& symbol_operation,const string& expression)
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

		//Writing values ​​to variables that need to be read
		int value1 = stoi(m[first][count_first - 2]);
		int value2 = stoi(m[second][count_second - 2]);


		pair<int, int> variables;
		variables.first = value1;
		variables.second = value2;
		
		return variables;
	}


	private:
	map<string, vector<string>> m;

};


Table file_to_table(const string& path)
{
	//Column names
	vector<string> column_names; 
	//Column data
	vector<string> table_data;
    //Row of cells from file
	string line_cells; 
	//One cell
	string cell; 
	//Object to read the file
	ifstream fs; 
	vector<vector<string>> lines_token;

	fs.open(path); //Opening a file

	
	if (!fs.is_open()) //Opening check
	{
		cout << "Ошибка открытия ффайла!" << endl;
	}
	else //If the file is open
	{
		if (getline(fs, line_cells))
		{
			stringstream data(line_cells);    //Putting data from a file into data
			while (getline(data, cell, ';'))  //Separating data from data, separately
			{
				column_names.push_back(cell); //Loading separated data into vector
			}
		}

		while (getline(fs, line_cells)) 
		{
			stringstream data(line_cells);   //Putting data from a file into data
			while (getline(data, cell, ';')) //Separating data from data, separately
			{
				table_data.push_back(cell);  //Loading separated data into vector
			}
		}

		//Tracking in if
		int counter_if = 0;
		//Vector cell tracking
		int counter_cells = 0;

		for (const string& cell : table_data) //Data separation
		{
			//vector to write to vector
			vector<string> j;  

			j.push_back(cell); // Add a cell to vector
			
			if (counter_if < column_names.size()) //Recording the first line
			{
				lines_token.push_back(j); 
				counter_if++; 
			}
			else //Recording the remaining lines
			{
				lines_token[counter_cells].push_back(cell);
				counter_cells++;

				if (counter_cells >= lines_token.size()) //Checking not to exceed the vector size
				{
					counter_cells = 0;
				}
			}
		}
		Table t(column_names, lines_token); 
		return t; //Returning column names and their data
	}


}



int main()
{
	setlocale(LC_ALL, "ru");

	//Variable to store the path to the file
	string path = "myfile1.csv"; 

	//Creating a table and loading data from a file into it
	Table table = file_to_table(path);

	cout << "\tИзначальная таблица:\n\n";
	//Table output
	table.display(); 
	//Processing all formulas
	table.search_formul(); 
	
	cout << "\n\tПосчитанная таблица:\n\n";
	//Table output again
	table.display();
	
	return 0;
}
