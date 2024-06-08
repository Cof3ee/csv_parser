#include "gtest/gtest.h"
#include "../../libraries/csv_parser_library/inc/Table.h"
#include "CsvParserException.h";
#include <string>
#include <map>
#include <vector>

using namespace std;

struct TableFixture : public testing::Test
{
	Table create_table()
	{
		vector<string> test_keys {"1", "2"};

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
	ASSERT_NO_THROW(Table t = create_table());
}

TEST_F(TableFixture, DisplayTest)
{
	Table t = create_table();

	ASSERT_NO_THROW(t.display());
}

TEST_F(TableFixture, evaluate_formulasTest)
{
	Table t = create_table();
	
	ASSERT_NO_THROW(t.evaluate_formulas());
}

TEST(CsvParserExceptioh, ConstructorTest)
{
	string expectedCell = "1";
	char expectedSymbol = '2';

	CsvParserException testClass(expectedSymbol, expectedCell);
	char actualSymbol = testClass.GetSymbol();
	string actualCell = testClass.GetCell();

	ASSERT_EQ(expectedCell, actualCell);
	ASSERT_EQ(expectedSymbol, actualSymbol);
}
TEST(CsvParserExceptioh, GetSymbolTest)
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