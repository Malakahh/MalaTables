#include "Table.h"
#include "TableData.h"

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
	//Make a copy of the list
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
	map.clear();
	keys.clear();
}

Table& Table::operator+=(const Table& rhs)
{
	//Insert rhs
	for (std::string k : rhs.keys)
	{
		if (!this->KeyExists(k)) //Key doesn't exist
		{
			std::unordered_map<std::string, BaseTableData*>::const_iterator got = rhs.map.find(k);
			this->map[k] = got->second->Copy();
			this->keys.push_back(k);
		}
	}

	return *this;
}

Table& Table::operator-=(const Table& rhs)
{
	//remove from lhs
	for (std::string k : rhs.keys)
	{
		if (this->KeyExists(k)) //Key exist
		{
			Remove(k);
		}
	}

	return *this;
}

Table operator+(const Table& lhs, const Table& rhs)
{
	Table t;

	//Insert lhs
	t += lhs;

	//Insert rhs
	t += rhs;

	return t;
}

Table operator-(const Table& lhs, const Table& rhs)
{
	Table t;

	//Insert lhs
	t += lhs;

	//Remove rhs
	t -= rhs;

	return t;
}

std::ostream& operator<<(std::ostream& s, const Table& table)
{
	Table t = table;

	s << "{" << std::endl;

	//Retrieve all keys
	std::list<std::string> keys;
	t.GetKeys(keys);

	//Pretty print all keys value pairs
	for (std::string k : keys)
	{
		s << "\t [\"" << k << "\"] = " << t.map[k]->ToString() << "," << std::endl;
	}

	s << "}";

	return s;
}

Table operator<<(Table& lhs, const Table& rhs)
{
	//Insert rhs
	for (std::string k : rhs.keys)
	{
		std::unordered_map<std::string, BaseTableData*>::const_iterator got = rhs.map.find(k);

		if (lhs.KeyExists(k))
			lhs.Remove(k);

		lhs.map[k] = got->second->Copy();
		lhs.keys.push_back(k);
	}

	return lhs;
}
