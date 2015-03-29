#include "Table.h"
#include "Test.h"
#include <iostream>

bool MyCompare(int a, int b)
{
	return a == b;
}

int main() {

	char c;

	Test t;
	t.StartTest(MyCompare);

	std::cout << std::endl << "Press any key to exit..." << std::endl;
	std::cin >> c;

	return 0;
}