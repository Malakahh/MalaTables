#pragma once
#include <sstream>
#include <unordered_map>
#include "TableData.cpp"

class Table
{
private:
	std::unordered_map<std::string, BaseTableData*> map; //Using a BaseTableData pointer to avoid slicing
public:
	Table();
	~Table();

	template <typename V> bool KeyExists(std::string key)
	{
		return map.count(key) > 0;
	}

	template <typename V> bool KeyExists(int key)
	{
		std::ostringstream s;
		s << key;
		return KeyExists<V>(s.str());
	}

	template <typename V> V Retrieve(std::string key)
	{
		std::unordered_map<std::string, BaseTableData*>::const_iterator got = map.find(key);
		TableData<V>* td = (TableData<V>*)got->second;
		V data = td->data;
		delete td;
		return data;
	}

	template <typename V> V Retrieve(int key)
	{
		std::ostringstream s;
		s << key;
		return Retrieve<V>(s.str());
	}

	template <typename V> void Add(std::string key, V value)
	{
		TableData<V>* tableData = new TableData<V>;
		tableData->data = value;

		this->map.insert({ key, tableData });
	}

	template <typename V> void Add(int key, V value)
	{
		std::ostringstream s;
		s << key;
		this->Add<V>(s.str(), value);
	}
};

