#pragma once
#include <memory>
#include <unordered_map>
#include "TableData.cpp"

class Table
{
private:
	std::unordered_map<int, BaseTableData*> map; //Using a BaseTableData pointer to avoid slicing

public:
	template <typename T> inline friend void AddToTable(Table &t, T item);

	Table();
	~Table();


};

