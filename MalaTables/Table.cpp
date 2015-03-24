#include "Table.h"
#include "TableData.cpp"

Table::Table()
{
}


Table::~Table()
{
	RemoveAll();
}

bool Table::KeyExists(const std::string key)
{
	return map.count(key) > 0;
}

bool Table::KeyExists(const int key)
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

void Table::Remove(const std::string key)
{
	map.erase(key);
	keys.remove(key);
}

void Table::Remove(const int key)
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


Table operator+(const Table& lhs, const Table& rhs)
{
	Table t;

	//Insert lhs
	for (std::string k : lhs.keys)
	{
		std::unordered_map<std::string, BaseTableData*>::const_iterator got = lhs.map.find(k);
		t.map[k] = got->second->Copy();
		t.keys.push_back(k);
	}

	//Insert rhs
	for (std::string k : rhs.keys)
	{
		if (lhs.map.count(k) == 0) //Key doesn't exist
		{
			std::unordered_map<std::string, BaseTableData*>::const_iterator got = rhs.map.find(k);
			t.map[k] = got->second->Copy();
			t.keys.push_back(k);
		}
	}
	
	//t.map.cbegin();

	return t;
}


std::ostream& operator<<(std::ostream& s, const Table& table)
{
	Table t = table;

	s << "{" << std::endl;

	std::list<std::string> keys;
	t.GetKeys(keys);
	for (std::string k : keys)
	{
		s << "\t [\"" << k << "\"] = " << t.map[k]->ToString() << "," << std::endl;
	}

	s << "}";

	return s;
}
