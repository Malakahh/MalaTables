#include "Table.h"
#include "Test.cpp"
#include <iostream>

int main() {

	char c;

	Test t;
	t.StartTest();

	std::cout << std::endl << "Press any key to exit..." << std::endl;
	std::cin >> c;

	return 0;
}