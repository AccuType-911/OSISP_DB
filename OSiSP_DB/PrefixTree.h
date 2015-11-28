#pragma once

#include "stdafx.h"
#include <vector>
#include <map>
#include <windows.h>


using namespace std;


template<class T>
class PrefixTree
{
private:
	// node data
	vector <T> data;
	map <WCHAR, PrefixTree<T> > subtrees;

	PrefixTree* find_subtree(WCHAR *key);

public:
	// constructors, destructors
	PrefixTree();
	virtual ~PrefixTree();
	
	// interface
	vector<T> find(WCHAR *key);
	void add(WCHAR *key, T value);
	bool contains_data();
};


template <class T>
PrefixTree<T>::PrefixTree()
{
}

template <class T>
PrefixTree<T>::~PrefixTree()
{
}

template <class T>
bool PrefixTree<T>::contains_data()
{
	return data.size() > 0;
}

template <class T>
PrefixTree<T>* PrefixTree<T>::find_subtree(WCHAR *key)
{
	if (key[0] == 0)
	{
		return this;
	}
	else
	{
		WCHAR ch = key[0];
		auto element = subtrees.find(ch);

		if (element == subtrees.end()) {
			return NULL;
		}

		return element->second.find_subtree(key + 1);
	}
}


template <class T>
vector<T> PrefixTree<T>::find(WCHAR *key)
{
	PrefixTree *tr = find_subtree(key);
	return tr->data;
}


template <class T>
void PrefixTree<T>::add(WCHAR *key, T value)
{
	if (key[0] == 0)
	{
		this->data.push_back(value);
	}
	else
	{
		WCHAR ch = key[0];
		subtrees[ch].add(key + 1, value);
	}
}