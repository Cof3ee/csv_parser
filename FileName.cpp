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

	Table(const vector<string>& keys, const  vector<vector<string>>& data) //��������� ����� �.�. �������� �������� � ������
	{
		//���������� ��� �������� �� ������
		int counter = 0;  

		for (const vector<string>& values : data) //������ ����� ������ ��� ��������
		{
			m.emplace(keys[counter++], values); 
		}
	}

	//����� ������� � ������ 
	void search_formul() 
	{
		for (auto& pair : m) //�������� ���� �� map
		{
			for (auto cell : pair.second) //������� ������ �� vector
			{
				for (char symbol : cell) //������ ������� ������� ���������� �: "="
				{
					if (symbol == '=')
					{
						search_mat_symbol(pair); //���� ������� �������, �� ���������� ������� �� ����� ������� ��������
					}
					break;
				}
			}
		}
	}

	//����� ������� �� �����
	void display()const
	{
		for (const auto & pair : m) //����� �������� ���������
		{
			cout << pair.first << '\t';
		}

		cout << endl;

		for (int counter = 0; counter < m.size(); counter++) //����� ��������� ������
		{
			for (const auto& pair : m) //��������� ����
			{
				if(counter <pair.second.size()) //���� ������� �� ��������� ������ vector
				{
				  cout << pair.second[counter] << '\t'; 
			    }
			}
			cout << endl;
		}
	}

private:

	//����� ������� ��� ��������
	void search_mat_symbol(pair< string, vector<string >> item)
	{
		for (auto cell : item.second) //������� ������ �� vector
		{
			for (char symbol : cell) //����� ������� ���. ��������
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

	//������� �����
	void evaluate_plus(pair< string, vector<string >> item)
	{
		//������� ��� ����������� ������ � ������� �������
		int count_vector = 0;

		for (auto cell : item.second) //������� ������ �� vector
		{
			for (char symbol : cell) //����� �������
			{
				if (symbol == '=')
				{
					// ������� ������� ������� "+"
					size_t plus_pos = cell.find('+');

					// ��������� ������ ����� ������ (����� "=" � �� "+")
					string first = cell.substr(1, plus_pos - 1);

					// ��������� ������ ����� ������ (����� "+")
					string second = cell.substr(plus_pos + 1);

					// ��������� ��������� ������ (�����)
					char first_digitChar = first.back();
					// ����������� ������ ����� � ����� (int)
					int count_first = first_digitChar - '0';
					// ������� ��������� ������ �� ������
					first.pop_back();
					
					char second_digitChar = second.back();
					int count_second = second_digitChar - '0';
					second.pop_back();

					//������ � ���������� �������� ������� ����� ���������
					int value1 = stoi(m[first][count_first - 2]);
					int value2 = stoi(m[second][count_second - 2]);

					int result = value1 + value2;

					//������� ������� � ������
					m[item.first][count_vector] = ""; 
					//������ ����� ������ � ������
					m[item.first][count_vector] = to_string(result);
				}
				break; //����� �� ������������� �� ���� ������
			}
			count_vector++; 
		}
	}
	//������� �������
	void evaluate_minus(pair< string, vector<string >> item)
	{
		//������� ��� ����������� ������ � ������� �������
		int count_vector = 0;

		for (auto cell : item.second) //������� ������ �� vector
		{
			for (char symbol : cell) //����� �������
			{
				if (symbol == '=')
				{
					// ������� ������� ������� "-"
					size_t minus_pos = cell.find('-');

					// ��������� ������ ����� ������ (����� "=" � �� "-")
					string first = cell.substr(1, minus_pos - 1);

					// ��������� ������ ����� ������ (����� "-")
					string second = cell.substr(minus_pos + 1);

					// ��������� ��������� ������ (�����)
					char first_digitChar = first.back();
					// ����������� ������ ����� � ����� (int)
					int count_first = first_digitChar - '0';
					// ������� ��������� ������ �� ������
					first.pop_back();

					char second_digitChar = second.back();
					int count_second = second_digitChar - '0';
					second.pop_back();

					//������ � ���������� �������� ������� ����� ���������
					int value1 = stoi(m[first][count_first - 2]);
					int value2 = stoi(m[second][count_second - 2]);

					int result = value1 - value2;

					//������� ������� � ������
					m[item.first][count_vector] = "";
					//������ ����� ������ � ������
					m[item.first][count_vector] = to_string(result);
				}
				break; //����� �� ������������� �� ���� ������
			}
			count_vector++;
		}
	}
	//������� ������������
	void evaluate_multiplication(pair< string, vector<string >> item)
	{
		//������� ��� ����������� ������ � ������� �������
		int count_vector = 0;

		for (auto cell : item.second) //������� ������ �� vector
		{
			for (char symbol : cell) //����� �������
			{
				if (symbol == '=')
				{
					// ������� ������� ������� "*"
					size_t multiplication_pos = cell.find('*');

					// ��������� ������ ����� ������ (����� "=" � �� "*")
					string first = cell.substr(1, multiplication_pos - 1);

					// ��������� ������ ����� ������ (����� "*")
					string second = cell.substr(multiplication_pos + 1);

					// ��������� ��������� ������ (�����)
					char first_digitChar = first.back();
					// ����������� ������ ����� � ����� (int)
					int count_first = first_digitChar - '0';
					// ������� ��������� ������ �� ������
					first.pop_back();

					char second_digitChar = second.back();
					int count_second = second_digitChar - '0';
					second.pop_back();

					//������ � ���������� �������� ������� ����� ���������
					int value1 = stoi(m[first][count_first - 2]);
					int value2 = stoi(m[second][count_second - 2]);

					int result = value1 * value2;

					//������� ������� � ������
					m[item.first][count_vector] = "";
					//������ ����� ������ � ������
					m[item.first][count_vector] = to_string(result);
				}
				break; //����� �� ������������� �� ���� ������
			}
			count_vector++;
		}
	}
	//������� �������
	void evaluate_segmentation(pair< string, vector<string >> item)
	{
		//������� ��� ����������� ������ � ������� �������
		int count_vector = 0;

		for (auto cell : item.second) //������� ������ �� vector
		{
			for (char symbol : cell) //����� �������
			{
				if (symbol == '=')
				{
					// ������� ������� ������� "/"
					size_t multiplication_pos = cell.find('/');

					// ��������� ������ ����� ������ (����� "=" � �� "/")
					string first = cell.substr(1, multiplication_pos - 1);

					// ��������� ������ ����� ������ (����� "/")
					string second = cell.substr(multiplication_pos + 1);

					// ��������� ��������� ������ (�����)
					char first_digitChar = first.back();
					// ����������� ������ ����� � ����� (int)
					int count_first = first_digitChar - '0';
					// ������� ��������� ������ �� ������
					first.pop_back();

					char second_digitChar = second.back();
					int count_second = second_digitChar - '0';
					second.pop_back();

					//������ � ���������� �������� ������� ����� ���������
					int value1 = stoi(m[first][count_first - 2]);
					int value2 = stoi(m[second][count_second - 2]);

					int result = value1 / value2;

					//������� ������� � ������
					m[item.first][count_vector] = "";
					//������ ����� ������ � ������
					m[item.first][count_vector] = to_string(result);
				}
				break; //����� �� ������������� �� ���� ������
			}
			count_vector++;
		}
	}

	private:
	map<string, vector<string>> m;

};


Table file_to_strings(const string& path)
{
	//�������� ��������
	vector<string> column_names; 
	//������ ��������
	vector<string> table_data;
    //������ ����� �� �����
	string line_cells; 
	//���� ������
	string cell; 
	//������� ��� ������ �����
	ifstream fs; 
	vector<vector<string>> lines_token;

	fs.open(path); //�������� �����

	
	if (!fs.is_open()) //�������� �� ��������
	{
		cout << "������ �������� ������!" << endl;
	}
	else //���� ���� ������
	{
		if (getline(fs, line_cells))
		{
			stringstream data(line_cells);    //��������� ������ �� ����� � data
			while (getline(data, cell, ';'))  //���������� ������ �� data, �� �����������
			{
				column_names.push_back(cell); //�������� ���������� ������ � vector
			}
		}

		while (getline(fs, line_cells)) 
		{
			stringstream data(line_cells);   //��������� ������ �� ����� � data
			while (getline(data, cell, ';')) //���������� ������ �� data, �� �����������
			{
				table_data.push_back(cell);  //�������� ���������� ������ � vector
			}
		}

		//������������ � if
		int counter_if = 0;
		//������������ ����� �������
		int counter_cells = 0;

		for (string cell : table_data) //���������� ������
		{
			//vector ��� ������ � vector
			vector<string> j;  

			j.push_back(cell); // ��������� ������ � vector
			
			if (counter_if < column_names.size()) //������ ������ �������
			{
				lines_token.push_back(j); 
				counter_if++; 
			}
			else //������ ��������� �������
			{
				lines_token[counter_cells].push_back(cell);
				counter_cells++;

				if (counter_cells >= lines_token.size()) //�������� ����� �� ����� �� ������ vector
				{
					counter_cells = 0;
				}
			}
		}

		Table t(column_names, lines_token); 
		return t; //���������� �������� �������� � �� ������

	}


}



int main()
{
	setlocale(LC_ALL, "ru");

	//���������� ��� �������� ���� � �����
	string path = "myfile1.csv"; 

	//�������� ������� � �������� � �� ������ �� �����
	Table table = file_to_strings(path);

	cout << "\t����������� �������:\n\n";
	//����� �������
	table.display(); 
	//��������� ���� ������
	table.search_formul(); 
	
	cout << "\n\t����������� �������:\n\n";
	//����� ����� �������
	table.display();



	return 0;
}
