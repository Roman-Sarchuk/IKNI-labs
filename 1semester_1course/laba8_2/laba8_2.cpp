#include "laba8_2.h"
using namespace std;



int main()
{
	string fpath = getPath();		// orders.txt
	//string fpath = "orders.txt";
	vector<Order> database{};
	pair<vector<Order>, vector<size_t>> searchDB({}, {});
	getData(database, fpath);

	size_t action;
	while (true)
	{
		cout << """::=::=::=::=::=::=::=::=::=::\n\
What to do?\n\
1) add a new record;\n\
2) search a record by field value;\n\
3) show records;\n\
4) edit a record;\n\
5) delete a record;\n\
6) sort by field value;\n\
7) exit the program.\n""" << endl;
		action = getActionNum(7);
		cout << "::=::=::=::=::=::=::=::=::=::\n\n" << endl;

		switch (action)
		{
		case 1:
			cout << "%-%-%-%-% ADD %-%-%-%-%" << endl;
			addRecord(database);
			appandRtoF(database[database.size() - 1], fpath);
			break;
		case 2:
			cout << "%-%-%-%-% SEARCH %-%-%-%-%" << endl;
			getSearchDB(database, fpath);
			break;
		case 3:
			cout << "%-%-%-%-% SHOW %-%-%-%-%" << endl;
			showDataBase(database, true);
			break;
		case 4:
			cout << "%-%-%-%-% EDIT %-%-%-%-%" << endl;
			searchDB = getSearchDB(database, fpath);
			cout << endl;

			if (searchDB.first.size() == 0)
				break;

			action = getActionNum(searchDB.first.size());	// Number of record
			action--;
			cout << endl;

			editRecord(database, searchDB.second[action]);
			updateFile(database, fpath);
			break;
		case 5:
			cout << "%-%-%-%-% DELETE %-%-%-%-%" << endl;
			searchDB = getSearchDB(database, fpath);
			cout << endl;

			if (searchDB.first.size() == 0)
				break;

			action = getActionNum(searchDB.first.size());	// Number of record
			action--;
			cout << endl;

			database.erase(database.begin() + searchDB.second[action]);
			cout << "! The deletion is completed !\n" << endl;
			updateFile(database, fpath);
			break;
		case 6:
			cout << "%-%-%-%-% SORT %-%-%-%-%" << endl;
			sortDataBase(database);
			updateFile(database, fpath);
			cout << "! The sorting is completed !\n" << endl;
			break;
		case 7:
			cout << "%-%-%-%-% EXIT %-%-%-%-%" << endl;
			return 0;
		}
		cout << "%-%-%-%-% -%- %-%-%-%-%\n\n" << endl;
	}

	system("PAUSE");
	return 0;
}