#ifndef MALATABLES_TEST
#define MALATABLES_TEST

#include "Table.h"

class Test
{
private:
	//Tests the Insert function of Table
	bool TestInsert(Table& t);

	//Tests the GetKeys function of Table
	bool TestGetKeys(Table& t);

	//Tests the Remove function of Table
	bool TestRemove(Table& t);

	//Tests insertion of nested tables
	bool TestNestedTables(Table& t);

	//Tests the + operator, and due to implementation, also += operator
	bool TestTableAddition();

	//Tests the - operator, and due to implementation, also -= operator
	bool TestTableSubtraction();

	//Tests the << operator
	bool TestTableBitwiseLeftShift();

	//Tests insertion of function pointers
	bool TestFuncPtr(bool(*f)(int, int));

public:
	//Run all tests and summerize results
	bool StartTest(bool(*f)(int, int));
};

#endif