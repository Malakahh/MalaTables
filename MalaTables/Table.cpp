#include "Table.h"
#include "TableData.cpp"

Table::Table()
{
}


Table::~Table()
{
	RemoveAll();
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

void Table::GetKeys(std::list<std::string> &keyVector)
{
	std::list<std::string> k(keys);
	keyVector = k;
}

void Table::Remove(std::string key)
{
	map.erase(key);
	keys.remove(key);
}

void Table::Remove(int key)
{
	std::ostringstream s;
	s << key;
	Remove(s.str());
}

void Table::RemoveAll()
{
	std::list<std::string> k;
	GetKeys(k);
	for (std::string key : k)
	{
		Remove(key);
	}
}

std::ostream& operator<<(std::ostream& s, Table& table)
{
	Table t = table;

	s << "Table = {" << std::endl;

	std::list<std::string> keys;
	t.GetKeys(keys);
	for (std::string k : keys)
	{
		s << "\t [\"" << k << "\"] = " << t.map[k]->ToString() << "," << std::endl;
	}

	s << "}" << std::endl;

	return s;
}
