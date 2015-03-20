#pragma once
#include "BaseTableData.h"
#include <iostream>
#include <string>

template<typename T> class TableData : BaseTableData
{
public:
	TableData();
	~TableData();

	T data;

};

template<typename T> std::ostream& operator<<(std::ostream &s, const TableData<T> &p);

