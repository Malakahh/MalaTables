#include "Test.h"

bool Test::TestInsert(Table& t)
{
	//Insert data
	std::cout << "Inserting some data..." << std::endl;
	t.Insert<std::string>(1, "testStr1");
	t.Insert<int>("strKey", 123456789);
	t.Insert<int>(-1, 20);

	//Print table
	std::cout << t << std::endl;


	bool one = false, two = false, three = false;
	std::cout << "Checking data..." << std::endl;

	//Test on first entry
	if (t.KeyExists(1) && t.Retrieve<std::string>(1) == "testStr1")
	{
		one = true;
		std::cout << "first entry: success!" << std::endl;
	}
	else
	{
		std::cout << "first entry: fail" << std::endl;
	}

	//Test on second entry
	if (t.KeyExists("strKey") && t.Retrieve<int>("strKey"))
	{
		two = true;
		std::cout << "second entry: success!" << std::endl;
	}
	else
	{
		std::cout << "second entry: fail" << std::endl;
	}

	//Test on third entry
	if (t.KeyExists(-1) && t.Retrieve<int>(-1) == 20)
	{
		three = true;
		std::cout << "third entry: sucecss!" << std::endl;
	}
	else
	{
		std::cout << "third entry: fail" << std::endl;
	}

	//Test on overwriting entries
	bool overwrite = false;
	std::cout << "Testing overwrite..." << std::endl;
	t.Insert<int>(-1, -1);
	if (t.KeyExists(-1) && t.Retrieve<int>(-1) == -1)
	{
		overwrite = true;
		std::cout << "overwrite entry: success!" << std::endl;
	}
	else
	{
		std::cout << "overwrite entry: fail" << std::endl;
	}

	std::cout << t << std::endl;

	return one && two && three && overwrite;
}

bool Test::TestGetKeys(Table& t)
{
	//Get list of all keys
	std::list<std::string> keys;
	t.GetKeys(keys);

	//Iterate through all keys and make sure they're all present in the table
	bool foundKeysExist = true;
	for (std::string k : keys)
	{
		if (t.KeyExists(k))
		{
			std::cout << "key " << k << ": success!" << std::endl;
		}
		else
		{
			std::cout << "key " << k << ": fail" << std::endl;
			foundKeysExist = false;
			break;
		}
	}

	std::cout << t << std::endl;

	return foundKeysExist;
}

bool Test::TestRemove(Table& t)
{
	//Remove an existing key
	std::cout << "removing key: -1" << std::endl;
	if (t.KeyExists(-1))
	{
		t.Remove(-1);
	}

	bool ret = false;

	//Check if the removed key exists in the table
	if (!t.KeyExists(-1))
	{
		ret = true;
		std::cout << "remove key: success!" << std::endl;
	}
	else
	{
		std::cout << "remove key: fail" << std::endl;
	}

	return ret;
}

bool Test::TestNestedTables(Table& t)
{
	//Insert some data, including a table
	Table tt;
	tt.Insert<int>(1, 777);
	tt.Insert<std::string>("str", "hello world!");
	t.Insert<Table>("tt", tt);

	//Print the parent table
	std::cout << t << std::endl;

	//Test if we inserted something into the key
	bool ret = false;
	if (t.KeyExists("tt"))
	{
		ret = true;
		std::cout << "table insert: success!" << std::endl;
	}
	else
	{
		std::cout << "table insert: fail" << std::endl;
	}

	return ret;
}

bool Test::TestTableAddition()
{
	Table t, t1, t2;
	//Insert data into two tables
	t1.Insert<std::string>(1, "one");
	t1.Insert<std::string>(2, "two");
	t1.Insert<std::string>(3, "three");

	t2.Insert<std::string>(3, "three in t2");
	t2.Insert<std::string>(4, "four");


	std::cout << "t1 = " << t1 << std::endl;
	std::cout << "t2 = " << t2 << std::endl;
	std::cout << "performaing addition..." << std::endl;

	//Perform the union with the + operator (as + relies on +=, both are tested)
	t = t1 + t2;
	std::cout << "t = " << t << std::endl;

	bool ret = true;

	//Test if data is consistent
	if (!(t.KeyExists(1) && t.Retrieve<std::string>(1) == "one" &&
		t.KeyExists(2) && t.Retrieve<std::string>(2) == "two" &&
		t.KeyExists(3) && t.Retrieve<std::string>(3) == "three" &&
		t.KeyExists(4) && t.Retrieve<std::string>(4) == "four"))
	{
		ret = false;
	}

	//Make sure data is copied, and we haven't just ended up with pointers to another table
	std::cout << "altering key 1..." << std::endl;
	t.Insert<std::string>(1, "onetyone");
	std::cout << t << std::endl;

	if (!(ret && t.KeyExists(1) && t.Retrieve<std::string>(1) == "onetyone") && //We have altered new object
		(t1.KeyExists(1) && t1.Retrieve<std::string>(1) == "one")) //Without altering the old one
	{
		ret = false;
		std::cout << "fail" << std::endl;
	}
	else
	{
		std::cout << "Success!" << std::endl;
	}

	return ret;
}

bool Test::TestTableSubtraction()
{
	Table t, t1, t2;

	//Insert data into two tables
	t1.Insert<std::string>(1, "one");
	t1.Insert<std::string>(2, "two");
	t1.Insert<std::string>(3, "three");

	t2.Insert<std::string>(3, "three in t2");
	t2.Insert<std::string>(4, "four");

	std::cout << "t1 = " << t1 << std::endl;
	std::cout << "t2 = " << t2 << std::endl;
	std::cout << "performing subtraction..." << std::endl;

	//Test the removal of intersection entries with the - operator (and due to implementation, the -= operator)
	t = t1 - t2;
	std::cout << "t = " << t << std::endl;

	bool ret = true;

	//Test if the data is consistent with the expected results
	if (!(t.KeyExists(1) && t.Retrieve<std::string>(1) == "one" &&
		t.KeyExists(2) && t.Retrieve<std::string>(2) == "two") &&
		(t.KeyExists(3) || !t.KeyExists(4)))
	{
		ret = false;
	}

	//Make sure we haven't altered the previous tables
	if (!(t1.KeyExists(3) && t1.Retrieve<std::string>(3) == "three" &&
		t2.KeyExists(3) && t2.Retrieve<std::string>(3) == "three in t2") &&
		ret)
	{
		ret = false;
	}

	return ret;
}

bool Test::TestTableBitwiseLeftShift()
{
	Table t1, t2;

	//Insert some data
	t1.Insert<std::string>(1, "one");
	t1.Insert<std::string>(2, "two");
	t1.Insert<std::string>(3, "three");

	t2.Insert<std::string>(3, "three in t2");
	t2.Insert<std::string>(4, "four");


	std::cout << "t1 = " << t1 << std::endl;
	std::cout << "t2 = " << t2 << std::endl;
	std::cout << "performaing leftshift..." << std::endl;

	//write everything from t2 to t1, overwriting any entries that shares a key
	t1 << t2;
	std::cout << "t1 = " << t1 << std::endl;

	bool ret = true;

	//Make sure result is consistent with expectations
	if (!(t1.KeyExists(1) && t1.Retrieve<std::string>(1) == "one" &&
		t1.KeyExists(2) && t1.Retrieve<std::string>(2) == "two" &&
		t1.KeyExists(3) && t1.Retrieve<std::string>(3) == "three in t2" &&
		t1.KeyExists(4) && t1.Retrieve<std::string>(4) == "four"))
	{
		ret = false;
	}

	//Altering an entry
	std::cout << "altering key 3..." << std::endl;
	t1.Insert<std::string>(3, "onetyone");
	std::cout << "t1 = " << t1 << std::endl;

	//Make sure we've only altered the new table
	if (!(ret && t1.KeyExists(3) && t1.Retrieve<std::string>(3) == "onetyone") && //We have altered new object
		(t2.KeyExists(3) && t2.Retrieve<std::string>(3) == "three in t2")) //Without altering the old one
	{
		ret = false;
		std::cout << "fail" << std::endl;
	}
	else
	{
		std::cout << "Success!" << std::endl;
	}

	return ret;
}

bool Test::TestFuncPtr(bool(*f)(int, int))
{
	Table t;

	//Insert a func ptr, passed to us from Main
	t.Insert<bool(*)(int, int)>(1, f);

	bool ret = true;

	if (t.KeyExists(1))
	{
		//Retrieve the function pointer
		bool(*Bar)(int, int) = t.Retrieve<bool(*)(int, int)>(1);

		//Test if the behavior of the function is consistent with expectations
		ret = Bar(1, 1);
		if (ret)
		{
			std::cout << "First call: succses!" << std::endl;

			ret = !Bar(1, 2);

			if (ret)
			{
				std::cout << "Second call: success!" << std::endl;
			}
			else
			{
				std::cout << "Second call: fail" << std::endl;
			}
		}
		else
		{
			std::cout << "First call: fail" << std::endl;
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}

bool Test::StartTest(bool(*f)(int, int))
{
	Table t;

	//Run each test

	std::cout << "***Testing insert***" << std::endl;
	bool testInsert = TestInsert(t);
	std::cout << std::endl;

	std::cout << "***Testing GetKeys***" << std::endl;
	bool testGetKeys = TestGetKeys(t);
	std::cout << std::endl;

	std::cout << "***Testing remove***" << std::endl;
	bool testRemove = TestRemove(t);
	std::cout << std::endl;

	std::cout << "***Testing nested tables***" << std::endl;
	bool testNestedTables = TestNestedTables(t);
	std::cout << std::endl;

	std::cout << "***Testing table Addition***" << std::endl;
	bool testTableAddition = TestTableAddition();
	std::cout << std::endl;

	std::cout << "***Testing table subtraction***" << std::endl;
	bool testTableSubtraction = TestTableSubtraction();
	std::cout << std::endl;

	std::cout << "***Testing table bitwise left shift***" << std::endl;
	bool testTableBitwiseLeftShift = TestTableBitwiseLeftShift();
	std::cout << std::endl;

	std::cout << "***Testing storage of function pointers***" << std::endl;
	bool testFuncPtr = TestFuncPtr(f);
	std::cout << std::endl;

	bool total = testInsert &&
		testGetKeys &&
		testRemove &&
		testNestedTables &&
		testTableAddition &&
		testTableSubtraction &&
		testTableBitwiseLeftShift &&
		testFuncPtr;

	//Summerize results
	std::cout << std::endl << "***Test Summary***" << std::endl;
	std::cout << "Insert: " << testInsert << std::endl;
	std::cout << "GetKeys: " << testGetKeys << std::endl;
	std::cout << "Remove: " << testRemove << std::endl;
	std::cout << "Nested tables: " << testNestedTables << std::endl;
	std::cout << "Table Addition: " << testTableAddition << std::endl;
	std::cout << "Table Subtraction: " << testTableSubtraction << std::endl;
	std::cout << "Table Bitwise Left Shift: " << testTableBitwiseLeftShift << std::endl;
	std::cout << "Test storage of function pointers: " << testFuncPtr << std::endl;

	std::cout << "Total: " << total << std::endl;

	return total;
}