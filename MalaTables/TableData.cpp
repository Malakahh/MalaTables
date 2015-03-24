#ifndef MALATABLES_TABLEDATA
#define MALATABLES_TABLEDATA

#include <iostream>

class BaseTableData {
public:
	virtual std::string ToString() = 0;
	virtual BaseTableData* Copy() = 0;
};

template<typename T> class TableData : public BaseTableData {
public:
	TableData<T>(const T data) : data(data) {}
	~TableData<T>();

	T data;

	std::string ToString() override
	{
		std::ostringstream s;
		s << data;
		return s.str();
	}

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