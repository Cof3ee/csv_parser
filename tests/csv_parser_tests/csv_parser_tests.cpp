#include "gtest/gtest.h"
#include "Table.h"
#include "CsvParserException.h";
#include <string>
#include <map>
#include <vector>

using namespace std;

struct TableFixture : public testing::Test
{
	Table create_table()
	{
		vector<string> test_keys {"A", "B"};

		vector<vector<string>> test_values;
		vector<string> value1{"Test 1", "Test 2"};
		vector<string> value2{"Test 10", "Test 20"};

		test_values.push_back(value1);
		test_values.push_back(value2);

		Table test_table(test_keys, test_values);
		
		return test_table;
	}
};


TEST_F(TableFixture, TableConstructorTest)
{
	ASSERT_NO_THROW(Table t());
}

TEST_F(TableFixture, DisplayTest)
{
	Table t = create_table();

	ASSERT_NO_THROW(t.display());
}

TEST_F(TableFixture, evaluate_formulasTest_no_formulas)
{
	Table table_test = create_table();
	Table t_original = create_table();

	table_test.evaluate_formulas();

	ASSERT_TRUE(table_test == t_original);
}

TEST_F(TableFixture, evaluate_formulasTest_formulas_calculated)
{
	vector<string> keys {"A","B","C"};
	vector<vector<string>> data;
	
	vector<string> value_1{"134", "20", "1"};
	vector<string> value_2{"55", "26", "12"};
	vector<string> value_3{"1", "29", "160"};
	
	data.push_back(value_1);
	data.push_back(value_2);
	data.push_back(value_3);
	
	Table original_table(keys, data);

	vector<string> test_keys {"A","B","C"};
	vector<vector<string>> test_data;
	
	vector<string> test_value_1{"134", "20", "1"};
	vector<string> test_value_2{"55", "26", "12"};
	vector<string> test_value_3{"1", "=B2-B3", "=A2+B3"};

	test_data.push_back(test_value_1);
	test_data.push_back(test_value_2);
    test_data.push_back(test_value_3);

	Table test_table(test_keys, test_data);

	test_table.evaluate_formulas();

	ASSERT_TRUE(test_table == original_table);
}

TEST_F(TableFixture, evaluate_formulasTest_unknown_operator)
{
	vector<string> test_keys {"A", "B", "C"};

	vector<vector<string>> test_data;
	vector<string> test_value_1{"134", "20", "1"};
	vector<string> test_value_2{"55", "26", "12"};
	vector<string> test_value_3{"1", "2", "=A2{B3"};

	test_data.push_back(test_value_1);
	test_data.push_back(test_value_2);
	test_data.push_back(test_value_3);

	Table test_table(test_keys, test_data);

	ASSERT_THROW(test_table.evaluate_formulas(),CsvParserException);
}

TEST_F(TableFixture, evaluate_formulasTest_sin_cos)
{
	vector<string> keys {"A", "B", "C"};
	vector<vector<string>> data;
	
	vector<string> value_1{"134", "20", "1"};
	vector<string> value_2{"55", "10", "12"};
	vector<string> value_3{"1", "-0.544021", "-0.839072"};

	data.push_back(value_1);
	data.push_back(value_2);
	data.push_back(value_3);
	
	Table original_table(keys, data);
	
	vector<string> test_keys {"A", "B", "C"};
	vector<vector<string>> test_data;
	
	vector<string> test_value_1{"134", "20", "1"};
	vector<string> test_value_2{"55", "10", "12"};
	vector<string> test_value_3{"1", "=SIN(B3)", "=COS(B3)"};

	test_data.push_back(test_value_1);
	test_data.push_back(test_value_2);
	test_data.push_back(test_value_3);

	Table test_table(test_keys, test_data);
	
	test_table.evaluate_formulas();

	ASSERT_TRUE(test_table == original_table);
}

TEST_F(TableFixture, evaluate_formulasTest_any_exception)
{
	Table t = create_table();
	
	ASSERT_NO_THROW(t.evaluate_formulas());
}

TEST(CsvParserException, ConstructorTest)
{
	string expectedCell = "1";
	char expectedSymbol = '2';

	CsvParserException testClass(expectedSymbol, expectedCell);
	char actualSymbol = testClass.GetSymbol();
	string actualCell = testClass.GetCell();

	ASSERT_EQ(expectedCell, actualCell);
	ASSERT_EQ(expectedSymbol, actualSymbol);
}
TEST(CsvParserException, GetSymbolTest)
{
	char expectedSymbol = 'q';
	string empty="";

	CsvParserException test(expectedSymbol, empty);
	char actualSymbol = test.GetSymbol();

	ASSERT_EQ(expectedSymbol, actualSymbol);
}

TEST(CsvParserException, GetCellTest)
{
	string expectedSymbol = "q";
	char empty=' ';

	CsvParserException test (empty,expectedSymbol);
	string actualSymbol = test.GetCell();

	ASSERT_EQ(expectedSymbol, actualSymbol);
}