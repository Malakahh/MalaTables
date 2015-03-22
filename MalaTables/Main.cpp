#include "Table.h"
#include <iostream>

void Test(Table &t)
{
	std::cout << "Inserting" << std::endl;
	t.Insert<std::string>(1, "test");
	t.Insert<int>("testies", 555555);

	std::cout << "Checking if key exists.." << std::endl;
	if (t.KeyExists(1))
	{
		std::cout << "Key exist! Printing value twice..." << std::endl;

		std::cout << "value: " << t.Retrieve<std::string>(1) << std::endl;
		std::cout << "value: " << t.Retrieve<std::string>(1) << std::endl;
	}
	else
	{
		std::cout << "Key doesn't exist" << std::endl;
	}

	std::cout << std::endl << "Testing GetKeys..." << std::endl;
	std::vector<std::string> keyss;
	t.GetKeys(keyss);
	for (auto k : keyss)
	{
		std::cout << "key: " << k << std::endl;
	}

	std::system("pause");
}

int main() {
	Table test;

	Test(test);

	return 0;
}