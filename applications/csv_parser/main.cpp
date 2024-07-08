#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "Table.h"
#include <cstdlib>
#include "CsvParserException.h"

using namespace std;

static Table file_to_table(const string& path)
{
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
		cout << "Ошибка открытия файла!" << endl;
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

int main(int argc,char* argv[])
{
	try
	{ 
	//Variable to store the path to the file
	string path;

		if (argc == 2) //User-supplied filename
		{
			 path = argv[1];
		}
		else //If the file name was not sent
		{
			path = "myfile1.csv";
		}

	setlocale(LC_ALL, "ru");

	//Creating a table and loading data from a file into it
	Table table = file_to_table(path);

	cout << "\tИзначальная таблица:\n\n";
	//Table output
	table.display(); 

	cout << endl;
	
			try
			{	//Processing all formulas
				table.evaluate_formulas(); //If the formula is found, then the function is called to search for the operation symbol
			}
			catch (CsvParserException& ex)
			{
				cout << "Incorrectly entered operation operator: ";
				cout << ex.GetSymbol() << " in cell: " << ex.GetCell() << endl;
			}
	
	cout << "\n\tПосчитанная таблица:\n\n";
	//Table output again
	table.display();
	
	system("pause");
	}
	
	catch (exception& ex)
	{
		cout << ex.what() << endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		cout << "Unknown Eror in main" << endl;
		return EXIT_FAILURE;
	}
	return 0;
}
