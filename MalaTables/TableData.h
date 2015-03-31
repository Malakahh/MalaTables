#ifndef MALATABLES_TABLEDATA
#define MALATABLES_TABLEDATA

#include "BaseTableData.h"

template<typename T> class TableData : public BaseTableData {
public:
	TableData<T>(const T data) : data(data) {}
	~TableData<T>();

	T data;

	//A ToString override abusing type T's bitwise left shift operator (<<)
	std::string ToString() override
	{
		std::ostringstream s;
		s << data;
		return s.str();
	}

	//Creates a copy of this object, and returns it as a pointer of its base type (to avoid slicing)
	BaseTableData* Copy() override
	{
		TableData<T>* t = new TableData<T>(data);
		return t;
	}
};

template<typename T> std::ostream& operator<<(std::ostream& s, const TableData<T>& td)
{
	s << td.ToString();
	return s;
}
#endif