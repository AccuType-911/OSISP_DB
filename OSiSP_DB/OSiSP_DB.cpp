// OSiSP_DB.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "PrefixTree.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "Human.h"

using namespace std;




void add(map<WCHAR *, vector<int>> *mp, PrefixTree<int> *tree, WCHAR *key, int value)
{
	(*mp)[key].push_back(value);
	(*tree).add(key, value);
}

void test_tree()
{
	map<WCHAR *, vector<int>> test_map;
	PrefixTree<int> tr;

	add(&test_map, &tr, L"\0", 4);
	add(&test_map, &tr, L"\0", 5);
	add(&test_map, &tr, L"a", 6);
	add(&test_map, &tr, L"ab", 7);
	add(&test_map, &tr, L"ab", 07);
	add(&test_map, &tr, L"aa", 8);
	add(&test_map, &tr, L"aaф", 9);
	add(&test_map, &tr, L"aaфф", 10);
	add(&test_map, &tr, L"aaфф", 11);

	vector<int> map_v, tree_v;
	map<WCHAR *, vector<int>>::iterator it = test_map.begin();

	for (; it != test_map.end(); it++)
	{
		WCHAR *key = it->first;
		map_v = it->second;
		tree_v = tr.find(key);

		// Ucomment to get the Debug Information:
		//wcout <<L"\n" << key <<L":\n\t";

		if (map_v.size() != tree_v.size())
		{
			wcerr << L"Error: Tree and map data isn't the same, because vector sizes are not the same!!!\n";
			return;
		}

		for (size_t i = 0; i < map_v.size(); i++) {
			if (map_v[i] != tree_v[i])
			{
				wcerr << L"Error: Tree and map data isn't the same, because vectors data are not the same!!!\n";
				return;
			}

			// Ucomment to get the Debug Information:
			//wcout << tree_v[i] << L" ";
		}
	}

	wcout << L"\nSuccess: Tree and map are the same. Tree is working!!!\n";
}


int wmain(int argc, char* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
	
	test_tree();


	WCHAR ch;
	wcin >> ch;

	return 0;
}

