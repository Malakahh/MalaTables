#ifndef MALATABLES_BASETABLEDATA
#define MALATABLES_BASETABLEDATA

#include <iostream>

class BaseTableData {
public:
	virtual std::string ToString() = 0;
	virtual BaseTableData* Copy() = 0;
};

#endif