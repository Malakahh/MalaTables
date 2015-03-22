#include "Table.h"


Table::Table()
{
}


Table::~Table()
{
}

bool Table::KeyExists(std::string key)
{
	return map.count(key) > 0;
}

bool Table::KeyExists(int key)
{
	std::ostringstream s;
	s << key;
	return KeyExists(s.str());
}

void Table::GetKeys(std::vector<std::string> &keyVector)
{
	std::vector<std::string> k(keys);
	keyVector = k;
}