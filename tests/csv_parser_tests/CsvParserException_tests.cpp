#include "gtest/gtest.h"
#include "CsvParserException.h";

using namespace std;

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
	string empty = "";

	CsvParserException test(expectedSymbol, empty);
	char actualSymbol = test.GetSymbol();

	ASSERT_EQ(expectedSymbol, actualSymbol);
}

TEST(CsvParserException, GetCellTest)
{
	string expectedSymbol = "q";
	char empty = ' ';

	CsvParserException test(empty, expectedSymbol);
	string actualSymbol = test.GetCell();

	ASSERT_EQ(expectedSymbol, actualSymbol);
}