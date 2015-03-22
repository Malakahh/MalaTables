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