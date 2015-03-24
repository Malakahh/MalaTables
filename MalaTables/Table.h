#ifndef MALATABLES_TABLE
#define MALATABLES_TABLE

#include <sstream>
#include <unordered_map>
#include "TableData.h"

class Table
{
private:
	//Unordered_map we use to store the data given to the table
	std::unordered_map<std::string, BaseTableData*> map; //Using a BaseTableData pointer to avoid slicing
	
	//A list to keep easily track of keys currently in the table
	std::list<std::string> keys;
public:
	Table();
	~Table();

	//Checks if the given key is present in the table
	bool KeyExists(const std::string key);

	//Checks if the given key is present in the table
	bool KeyExists(const int key);

	//Returns all keys stored in the table
	void GetKeys(std::list<std::string> &keyVector);

	//Removes the entry at key
	void Remove(const std::string key);

	//Removes the entry at key
	void Remove(const int key);

	//Removes all entries
	void RemoveAll();

	//Gets a value at key
	template <typename V> V Retrieve(const std::string key)
	{
		std::unordered_map<std::string, BaseTableData*>::const_iterator got = map.find(key);
		TableData<V>* td = dynamic_cast<TableData<V>*>(got->second);
		return td->data;
	}

	//Gets a value at key
	template <typename V> V Retrieve(const int key)
	{
		std::ostringstream s;
		s << key;
		return Retrieve<V>(s.str());
	}

	//Inserts a value into the table at key
	template <typename V> void Insert(const std::string key, const V value)
	{
		TableData<V>* tableData = new TableData<V>(value);

		//Make sure to properly remove key if it already exist
		if (KeyExists(key))
		{
			Remove(key);
		}

		map.insert({ key, tableData });
		keys.push_back(key);
	}

	//Inserts a value into the table at key
	template <typename V> void Insert(const int key, const V value)
	{
		std::ostringstream s;
		s << key;
		Insert<V>(s.str(), value);
	}

	//Union all entries from rhs into lhs without overwriting existing keys.
	Table& operator+=(const Table& rhs);

	//Removes any intersecting entries from lhs.
	Table& operator-=(const Table& rhs);

	//Union all entries from rhs into lhs without overwriting existing keys.
	friend Table operator+(const Table& lhs, const Table& rhs);

	//Removes any intersecting entries from lhs.
	friend Table operator-(const Table& lhs, const Table& rhs);

	//Writes to an output stream, i.e. std::cout.
	friend std::ostream& operator<<(std::ostream& s, const Table& table);

	//Writes entries from rhs to lhs, overwriting any existing keys
	friend Table operator<<(Table& lhs, const Table& rhs);
};

#endif