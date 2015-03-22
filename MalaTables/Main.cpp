#include "Table.h"
#include <iostream>

int main() {
	Table t;
	std::string s;
	t.Add<std::string>(1, "test");
	if (t.KeyExists(1))
	{
		std::cout << "value: " << t.Retrieve<std::string>(1) << std::endl;
		std::cout << "value: " << t.Retrieve<std::string>(1) << std::endl;
	}
	else
		std::cout << "Key doesn't exist" << std::endl;

	std::system("pause");

	return 0;
}