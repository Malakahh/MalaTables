#ifndef MALATABLES_TEST
#define MALATABLES_TEST

#include "Table.h"
#include <iostream>

using namespace std;

class Test
{
public:
	bool TestInsert(Table &t)
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

	bool TestGetKeys(Table& t)
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

	bool TestRemove(Table& t)
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

	bool TestNestedTables(Table& t)
	{
		Table tt;
		tt.Insert<int>(1, 777);
		tt.Insert<string>("str", "hello world!");
		t.Insert<Table>("tt", tt);
		cout << t << endl;

		bool ret = false;
		if (t.KeyExists("tt"))
		{
			ret = true;
			cout << "table insert: success!" << endl;
		}
		else
		{
			cout << "table insert: fail" << endl;
		}

		return ret;
	}

	bool TestTableAddition()
	{
		Table t, t1, t2;
	
		t1.Insert<string>(1, "one");
		t1.Insert<string>(2, "two");
		t1.Insert<string>(3, "three");
	
		t2.Insert<string>(3, "three in t2");
		t2.Insert<string>(4, "four");


		cout << "t1 = " << t1 << endl;
		cout << "t2 = " << t2 << endl;
		cout << "performaing addition..." << endl;
	
		t = t1 + t2;
		cout << "t = " << t << endl;
	
		bool ret = true;

		if (!(t.KeyExists(1) && t.Retrieve<string>(1) == "one" &&
			t.KeyExists(2) && t.Retrieve<string>(2) == "two" &&
			t.KeyExists(3) && t.Retrieve<string>(3) == "three" &&
			t.KeyExists(4) && t.Retrieve<string>(4) == "four"))
		{
			ret = false;
		}

		cout << "altering key 1..." << endl;
		t.Insert<string>(1, "onetyone");
		cout << t << endl;

		if (!(ret && t.KeyExists(1) && t.Retrieve<string>(1) == "onetyone") && //We have altered new object
			(t1.KeyExists(1) && t1.Retrieve<string>(1) == "one")) //Without altering the old one
		{
			ret = false;
			cout << "fail" << endl;
		}
		else
		{
			cout << "Success!" << endl;
		}

		return ret;
	}

	bool TestTableSubtraction()
	{
		Table t, t1, t2;

		t1.Insert<string>(1, "one");
		t1.Insert<string>(2, "two");
		t1.Insert<string>(3, "three");

		t2.Insert<string>(3, "three in t2");
		t2.Insert<string>(4, "four");

		cout << "t1 = " << t1 << endl;
		cout << "t2 = " << t2 << endl;
		cout << "performing subtraction..." << endl;

		t = t1 - t2;
		cout << "t = " << t << endl;

		bool ret = true;

		if (!(t.KeyExists(1) && t.Retrieve<string>(1) == "one" &&
			t.KeyExists(2) && t.Retrieve<string>(2) == "two") &&
			(t.KeyExists(3) || !t.KeyExists(4)))
		{
			ret = false;
		}

		if (!(t1.KeyExists(3) && t1.Retrieve<string>(3) == "three" &&
			t2.KeyExists(3) && t2.Retrieve<string>(3) == "three in t2") &&
			ret)
		{
			ret = false;
		}

		return ret;
	}

	bool TestTableBitwiseLeftShift()
	{
		Table t1, t2;

		t1.Insert<string>(1, "one");
		t1.Insert<string>(2, "two");
		t1.Insert<string>(3, "three");

		t2.Insert<string>(3, "three in t2");
		t2.Insert<string>(4, "four");


		cout << "t1 = " << t1 << endl;
		cout << "t2 = " << t2 << endl;
		cout << "performaing leftshift..." << endl;

		t1 << t2;
		cout << "t1 = " << t1 << endl;

		bool ret = true;

		if (!(t1.KeyExists(1) && t1.Retrieve<string>(1) == "one" &&
			t1.KeyExists(2) && t1.Retrieve<string>(2) == "two" &&
			t1.KeyExists(3) && t1.Retrieve<string>(3) == "three in t2" &&
			t1.KeyExists(4) && t1.Retrieve<string>(4) == "four"))
		{
			ret = false;
		}

		cout << "altering key 3..." << endl;
		t1.Insert<string>(3, "onetyone");
		cout << "t1 = " << t1 << endl;

		if (!(ret && t1.KeyExists(3) && t1.Retrieve<string>(3) == "onetyone") && //We have altered new object
			(t2.KeyExists(3) && t2.Retrieve<string>(3) == "three in t2")) //Without altering the old one
		{
			ret = false;
			cout << "fail" << endl;
		}
		else
		{
			cout << "Success!" << endl;
		}

		return ret;
	}

	bool StartTest()
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

		cout << "***Testing nested tables***" << endl;
		bool testNestedTables = TestNestedTables(t);
		cout << endl;

		cout << "***Testing table Addition***" << endl;
		bool testTableAddition = TestTableAddition();
		cout << endl;

		cout << "***Testing table subtraction***" << endl;
		bool testTableSubtraction = TestTableSubtraction();
		cout << endl;

		cout << "***Testing table bitwise left shift***" << endl;
		bool testTableBitwiseLeftShift = TestTableBitwiseLeftShift();
		cout << endl;

		bool total = testInsert &&
			testGetKeys &&
			testRemove &&
			testNestedTables &&
			testTableAddition &&
			testTableSubtraction &&
			testTableBitwiseLeftShift;
	
		cout << endl << "***Test Summary***" << endl;
		cout << "Insert: " << testInsert << endl;
		cout << "GetKeys: " << testGetKeys << endl;
		cout << "Remove: " << testRemove << endl;
		cout << "Nested tables: " << testNestedTables << endl;
		cout << "Table Addition: " << testTableAddition << endl;
		cout << "Table Subtraction: " << testTableSubtraction << endl;
		cout << "Table Bitwise Left Shift: " << testTableBitwiseLeftShift << endl;

		cout << "Total: " << total << endl;

		return total;
	}
};
#endif