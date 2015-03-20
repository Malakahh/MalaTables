#pragma once
#include "Table.h"
#include "TableData.cpp"
#include <iostream>
#include <typeinfo>

template <typename T> void AddToTable(Table &t, T item){
	TableData<T> tableData;
	tableData.data = item;
	
	t.map.insert({ 1, &tableData });

	std::unordered_map<int, BaseTableData*>::const_iterator got = t.map.find(1);
	TableData<T>* td = (TableData<T>*)got->second;
	std::cout << *td << std::endl;
}