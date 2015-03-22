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

	bool KeyExists(std::string key);
	bool KeyExists(int key);
	void GetKeys(std::list<std::string> &keyVector);
	void Remove(std::string key);
	void Remove(int key);
	void RemoveAll();

	template <typename V> V Retrieve(std::string key)
	{
		std::unordered_map<std::string, BaseTableData*>::const_iterator got = map.find(key);
		TableData<V>* td = (TableData<V>*)got->second;
		V data = td->data;
		return data;
	}

	template <typename V> V Retrieve(int key)
	{
		std::ostringstream s;
		s << key;
		return Retrieve<V>(s.str());
	}

	template <typename V> void Insert(std::string key, V value)
	{
		TableData<V>* tableData = new TableData<V>;
		tableData->data = value;

		if (KeyExists(key))
		{
			Remove(key);
		}

		map.insert({ key, tableData });
		keys.push_back(key);
	}

	template <typename V> void Insert(int key, V value)
	{
		std::ostringstream s;
		s << key;
		Insert<V>(s.str(), value);
	}
};

#endif