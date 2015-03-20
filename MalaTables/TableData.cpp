#pragma once
#include <iostream>
#include <string>

struct BaseTableData {
};

template<typename T> struct TableData : public BaseTableData {
	T data;
};

template<typename T> std::ostream& operator<<(std::ostream& s, const TableData<T>& td)
{
	s << "hi";
	return s;
}