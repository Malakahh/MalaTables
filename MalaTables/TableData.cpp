#pragma once
#include <iostream>

struct BaseTableData {
};

template<typename T> struct TableData : public BaseTableData {
	T data;
};

template<typename T> std::ostream& operator<<(std::ostream& s, const TableData<T>& td)
{
	s << td.data;
	return s;
}