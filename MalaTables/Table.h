#ifndef MALATABLES_TABLE
#define MALATABLES_TABLE

#include <sstream>
#include <unordered_map>
#include "TableData.cpp"

class Table
{
private:
	std::unordered_map<std::string, BaseTableData*> map; //Using a BaseTableData pointer to avoid slicing
	std::list<std::string> keys;
public:
	Table();
	~Table();

	#pragma region Methods

	bool KeyExists(const std::string key);
	bool KeyExists(const int key);
	void GetKeys(std::list<std::string> &keyVector);
	void Remove(const std::string key);
	void Remove(const int key);
	void RemoveAll();

	template <typename V> V Retrieve(const std::string key)
	{
		std::unordered_map<std::string, BaseTableData*>::const_iterator got = map.find(key);
		TableData<V>* td = (TableData<V>*)got->second;
		V data = td->data;
		return data;
	}

	template <typename V> V Retrieve(const int key)
	{
		std::ostringstream s;
		s << key;
		return Retrieve<V>(s.str());
	}

	template <typename V> void Insert(const std::string key, const V value)
	{
		TableData<V>* tableData = new TableData<V>(value);

		if (KeyExists(key))
		{
			Remove(key);
		}

		map.insert({ key, tableData });
		keys.push_back(key);
	}

	template <typename V> void Insert(const int key, const V value)
	{
		std::ostringstream s;
		s << key;
		Insert<V>(s.str(), value);
	}

	#pragma endregion
	#pragma region OperatorOverloads

	/*
		Inserts all entries from rhs into lhs without overwriting existing keys.
	*/
	friend Table operator+(const Table& lhs, const Table& rhs);
	friend Table operator-(const Table& lhs, const Table& rhs);

	/*
		Writes to an output stream, i.e. std::cout.
	*/
	friend std::ostream& operator<<(std::ostream& s, const Table& table);


	friend Table operator<<(Table& lhs, const Table& ths);
	Table operator+=(const Table& t);
	Table operator-=(const Table& t);
	#pragma endregion
};

#endif