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
	std::list<std::string> keyss;
	t.GetKeys(keyss);
	for (auto k : keyss)
	{
		std::cout << "key: " << k << std::endl;
	}

	std::cout << std::endl << "Testing remove..." << std::endl;
	t.Insert<int>(-1, -1);
	std::cout << "added additional key, printing keys..." << std::endl;
	std::list<std::string> preR;
	t.GetKeys(preR);
	for (auto k : preR)
	{
		std::cout << "key: " << k << std::endl;
	}
	std::cout << "Attempting to remove key" << std::endl;
	t.Remove(-1);
	std::cout << "printing keys post remove..." << std::endl;
	std::list<std::string> postR;
	t.GetKeys(postR);
	for (auto k : postR)
	{
		std::cout << "key: " << k << std::endl;
	}
	std::cout << "Key exists: " << t.KeyExists(-1) << std::endl;



	std::cout << std::endl << std::endl;
	std::system("pause");
}

int main() {
	Table test;

	Test(test);

	return 0;
}