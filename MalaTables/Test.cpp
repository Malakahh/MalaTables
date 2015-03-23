#ifndef MALATABLES_TEST
#define MALATABLES_TEST

#include "Table.h"
#include <iostream>

using namespace std;


inline bool TestInsert(Table &t)
{
	cout << "Inserting some data..." << endl;
	t.Insert<string>(1, "testStr1");
	t.Insert<int>("strKey", 123456789);
	t.Insert<int>(-1, 20);

	cout << t << endl;

	bool one = false, two = false, three = false;
	cout << "Checking data..." << endl;

	if (t.KeyExists(1) && t.Retrieve<string>(1) == "testStr1")
	{
		one = true;
		cout << "first entry: success!" << endl;
	}
	else
	{
		cout << "first entry: fail" << endl;
	}

	if (t.KeyExists("strKey") && t.Retrieve<int>("strKey"))
	{
		two = true;
		cout << "second entry: success!" << endl;
	}
	else
	{
		cout << "second entry: fail" << endl;
	}

	if (t.KeyExists(-1) && t.Retrieve<int>(-1) == 20)
	{
		three = true;
		cout << "third entry: sucecss!" << endl;
	}
	else
	{
		cout << "third entry: fail" << endl;
	}

	bool overwrite = false;
	cout << "Testing overwrite..." << endl;
	t.Insert<int>(-1, -1);
	if (t.KeyExists(-1) && t.Retrieve<int>(-1) == -1)
	{
		overwrite = true;
		cout << "overwrite entry: success!" << endl;
	}
	else
	{
		cout << "overwrite entry: fail" << endl;
	}

	cout << t << endl;

	return one && two && three && overwrite;
}

inline bool TestGetKeys(Table& t)
{
	list<string> keys;
	t.GetKeys(keys);
	bool foundKeysExist = true;
	for (string k : keys)
	{
		if (t.KeyExists(k))
		{
			cout << "key " << k << ": success!" << endl;
		}
		else
		{
			cout << "key " << k << ": fail" << endl;
			foundKeysExist = false;
			break;
		}
	}

	cout << t << endl;

	return foundKeysExist;
}

inline bool TestRemove(Table& t)
{
	cout << "removing key: -1" << endl;
	if (t.KeyExists(-1))
	{
		t.Remove(-1);
	}

	bool ret = false;

	if (!t.KeyExists(-1))
	{
		ret = true;
		cout << "remove key: success!" << endl;
	}
	else
	{
		cout << "remove key: fail" << endl;
	}

	return ret;
}

inline bool Test()
{
	Table t;

	cout << "***Testing insert***" << endl;
	bool testInsert = TestInsert(t);
	cout << endl;

	cout << "***Testing GetKeys***" << endl;
	bool testGetKeys = TestGetKeys(t);
	cout << endl;

	cout << "***Testing remove***" << endl;
	bool testRemove = TestRemove(t);
	cout << endl;


	bool total = testInsert &&
		testGetKeys &&
		testRemove;
	
	cout << endl << "***Test Summary***" << endl;
	cout << "Insert: " << testInsert << endl;
	cout << "GetKeys: " << testGetKeys << endl;
	cout << "Remove: " << testRemove << endl;

	cout << "Total: " << total << endl;

	return total;
}

#endif