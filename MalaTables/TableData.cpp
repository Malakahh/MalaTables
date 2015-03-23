#ifndef MALATABLES_TABLEDATA
#define MALATABLES_TABLEDATA

#include <iostream>

struct BaseTableData {
	virtual std::string ToString() = 0;
};

template<typename T> struct TableData : public BaseTableData {
//public:
	T data;

	std::string ToString() override
	{
		std::ostringstream s;
		s << data;
		return s.str();
	}
};

template<typename T> std::ostream& operator<<(std::ostream& s, TableData<T>& td)
{
	s << td.ToString();
	return s;
}

#endif