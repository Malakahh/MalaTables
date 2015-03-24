#ifndef MALATABLES_TABLEDATA
#define MALATABLES_TABLEDATA

#include <iostream>

class BaseTableData {
public:
	virtual std::string ToString() = 0;
};

template<typename T> class TableData : public BaseTableData {
public:
	T data;

	std::string ToString() override
	{
		std::ostringstream s;
		s << data;
		return s.str();
	}
};

template<typename T> std::ostream& operator<<(std::ostream& s, const TableData<T>& td)
{
	s << td.ToString();
	return s;
}

#endif