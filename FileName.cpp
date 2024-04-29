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

	Table(const vector<string>& keys, const  vector<vector<string>>& data) //Принимаем ключи т.е. названия столбцов и данные
	{
		//Переменная для итерация по ключам
		int counter = 0;  

		for (const vector<string>& values : data) //Запись своих данных для столбцов
		{
			m.emplace(keys[counter++], values); 
		}
	}

	//Поиск формулы в ячейке 
	void search_formul() 
	{
		for (auto& pair : m) //Вытащить пару из map
		{
			for (auto cell : pair.second) //Извлечь ячейку из vector
			{
				for (char symbol : cell) //Поиска формулы которая начинается с: "="
				{
					if (symbol == '=')
					{
						search_mat_symbol(pair); //Если формула найдена, то вызывается функция на поиск символа операции
					}
					break;
				}
			}
		}
	}

	//Вывод таблицы на экран
	void display()const
	{
		for (const auto & pair : m) //Вывод названий столбиков
		{
			cout << pair.first << '\t';
		}

		cout << endl;

		for (int counter = 0; counter < m.size(); counter++) //Вывод остальных данных
		{
			for (const auto& pair : m) //Извлекаем пару
			{
				if(counter <pair.second.size()) //Если счётчик не превышает размер vector
				{
				  cout << pair.second[counter] << '\t'; 
			    }
			}
			cout << endl;
		}
	}

private:

	//Поиск символа мат операции
	void search_mat_symbol(pair< string, vector<string >> item)
	{
		for (auto cell : item.second) //Извлечь ячейку из vector
		{
			for (char symbol : cell) //Поиск символа мат. операции
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

	//Подсчёт суммы
	void evaluate_plus(pair< string, vector<string >> item)
	{
		//Счётчик для обозначения ячейки в которой формула
		int count_vector = 0;

		for (auto cell : item.second) //Извлечь ячейку из vector
		{
			for (char symbol : cell) //Поиск формулы
			{
				if (symbol == '=')
				{
					// Находим позицию символа "+"
					size_t plus_pos = cell.find('+');

					// Извлекаем первую часть строки (после "=" и до "+")
					string first = cell.substr(1, plus_pos - 1);

					// Извлекаем вторую часть строки (после "+")
					string second = cell.substr(plus_pos + 1);

					// Извлекаем последний символ (цифру)
					char first_digitChar = first.back();
					// Преобразуем символ цифры в число (int)
					int count_first = first_digitChar - '0';
					// Удаляем последний символ из строки
					first.pop_back();
					
					char second_digitChar = second.back();
					int count_second = second_digitChar - '0';
					second.pop_back();

					//Запись в переменные значений которые нужно посчитать
					int value1 = stoi(m[first][count_first - 2]);
					int value2 = stoi(m[second][count_second - 2]);

					int result = value1 + value2;

					//Очистка формулы в ячейке
					m[item.first][count_vector] = ""; 
					//Запись новых данных в ячейку
					m[item.first][count_vector] = to_string(result);
				}
				break; //Чтобы не итерироваться по всей ячейке
			}
			count_vector++; 
		}
	}
	//Подсчёт разницы
	void evaluate_minus(pair< string, vector<string >> item)
	{
		//Счётчик для обозначения ячейки в которой формула
		int count_vector = 0;

		for (auto cell : item.second) //Извлечь ячейку из vector
		{
			for (char symbol : cell) //Поиск формулы
			{
				if (symbol == '=')
				{
					// Находим позицию символа "-"
					size_t minus_pos = cell.find('-');

					// Извлекаем первую часть строки (после "=" и до "-")
					string first = cell.substr(1, minus_pos - 1);

					// Извлекаем вторую часть строки (после "-")
					string second = cell.substr(minus_pos + 1);

					// Извлекаем последний символ (цифру)
					char first_digitChar = first.back();
					// Преобразуем символ цифры в число (int)
					int count_first = first_digitChar - '0';
					// Удаляем последний символ из строки
					first.pop_back();

					char second_digitChar = second.back();
					int count_second = second_digitChar - '0';
					second.pop_back();

					//Запись в переменные значений которые нужно посчитать
					int value1 = stoi(m[first][count_first - 2]);
					int value2 = stoi(m[second][count_second - 2]);

					int result = value1 - value2;

					//Очистка формулы в ячейке
					m[item.first][count_vector] = "";
					//Запись новых данных в ячейку
					m[item.first][count_vector] = to_string(result);
				}
				break; //Чтобы не итерироваться по всей ячейке
			}
			count_vector++;
		}
	}
	//Подсчёт произведения
	void evaluate_multiplication(pair< string, vector<string >> item)
	{
		//Счётчик для обозначения ячейки в которой формула
		int count_vector = 0;

		for (auto cell : item.second) //Извлечь ячейку из vector
		{
			for (char symbol : cell) //Поиск формулы
			{
				if (symbol == '=')
				{
					// Находим позицию символа "*"
					size_t multiplication_pos = cell.find('*');

					// Извлекаем первую часть строки (после "=" и до "*")
					string first = cell.substr(1, multiplication_pos - 1);

					// Извлекаем вторую часть строки (после "*")
					string second = cell.substr(multiplication_pos + 1);

					// Извлекаем последний символ (цифру)
					char first_digitChar = first.back();
					// Преобразуем символ цифры в число (int)
					int count_first = first_digitChar - '0';
					// Удаляем последний символ из строки
					first.pop_back();

					char second_digitChar = second.back();
					int count_second = second_digitChar - '0';
					second.pop_back();

					//Запись в переменные значений которые нужно посчитать
					int value1 = stoi(m[first][count_first - 2]);
					int value2 = stoi(m[second][count_second - 2]);

					int result = value1 * value2;

					//Очистка формулы в ячейке
					m[item.first][count_vector] = "";
					//Запись новых данных в ячейку
					m[item.first][count_vector] = to_string(result);
				}
				break; //Чтобы не итерироваться по всей ячейке
			}
			count_vector++;
		}
	}
	//Подсчёт деления
	void evaluate_segmentation(pair< string, vector<string >> item)
	{
		//Счётчик для обозначения ячейки в которой формула
		int count_vector = 0;

		for (auto cell : item.second) //Извлечь ячейку из vector
		{
			for (char symbol : cell) //Поиск формулы
			{
				if (symbol == '=')
				{
					// Находим позицию символа "/"
					size_t multiplication_pos = cell.find('/');

					// Извлекаем первую часть строки (после "=" и до "/")
					string first = cell.substr(1, multiplication_pos - 1);

					// Извлекаем вторую часть строки (после "/")
					string second = cell.substr(multiplication_pos + 1);

					// Извлекаем последний символ (цифру)
					char first_digitChar = first.back();
					// Преобразуем символ цифры в число (int)
					int count_first = first_digitChar - '0';
					// Удаляем последний символ из строки
					first.pop_back();

					char second_digitChar = second.back();
					int count_second = second_digitChar - '0';
					second.pop_back();

					//Запись в переменные значений которые нужно посчитать
					int value1 = stoi(m[first][count_first - 2]);
					int value2 = stoi(m[second][count_second - 2]);

					int result = value1 / value2;

					//Очистка формулы в ячейке
					m[item.first][count_vector] = "";
					//Запись новых данных в ячейку
					m[item.first][count_vector] = to_string(result);
				}
				break; //Чтобы не итерироваться по всей ячейке
			}
			count_vector++;
		}
	}

	private:
	map<string, vector<string>> m;

};


Table file_to_strings(const string& path)
{
	//Названия столбцов
	vector<string> column_names; 
	//Данные столбцов
	vector<string> table_data;
    //Строка ячеек из файла
	string line_cells; 
	//Одна ячейка
	string cell; 
	//Объекта для чтения файла
	ifstream fs; 
	vector<vector<string>> lines_token;

	fs.open(path); //Открытие файла

	
	if (!fs.is_open()) //Проверка на открытие
	{
		cout << "Ошибка открытия ффайла!" << endl;
	}
	else //Если файл открыт
	{
		if (getline(fs, line_cells))
		{
			stringstream data(line_cells);    //Помещение данных из файла в data
			while (getline(data, cell, ';'))  //Разделение данных из data, по отдельности
			{
				column_names.push_back(cell); //Загрузка разделённых данных в vector
			}
		}

		while (getline(fs, line_cells)) 
		{
			stringstream data(line_cells);   //Помещение данных из файла в data
			while (getline(data, cell, ';')) //Разделение данных из data, по отдельности
			{
				table_data.push_back(cell);  //Загрузка разделённых данных в vector
			}
		}

		//Отслеживание в if
		int counter_if = 0;
		//Отслеживание ячеек вектора
		int counter_cells = 0;

		for (string cell : table_data) //Разделение данных
		{
			//vector для записи в vector
			vector<string> j;  

			j.push_back(cell); // Добавляем ячейку в vector
			
			if (counter_if < column_names.size()) //Запись первой строчки
			{
				lines_token.push_back(j); 
				counter_if++; 
			}
			else //Запись остальных строчек
			{
				lines_token[counter_cells].push_back(cell);
				counter_cells++;

				if (counter_cells >= lines_token.size()) //Проверка чтобы не выйти за размер vector
				{
					counter_cells = 0;
				}
			}
		}

		Table t(column_names, lines_token); 
		return t; //Возвращаем названия столбцов и их данные

	}


}



int main()
{
	setlocale(LC_ALL, "ru");

	//Переменная для хранения пути к файлу
	string path = "myfile1.csv"; 

	//Создание даблицы и загрузка в неё данных из файла
	Table table = file_to_strings(path);

	cout << "\tИзначальная таблица:\n\n";
	//Вывод таблицы
	table.display(); 
	//Обработка всех формул
	table.search_formul(); 
	
	cout << "\n\tПосчитанная таблица:\n\n";
	//Снова вывод таблицы
	table.display();



	return 0;
}
