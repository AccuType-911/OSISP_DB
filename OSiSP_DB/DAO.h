#pragma once

#include <string>
#include <vector>
#include "Human.h"


using namespace std;


class DAO
{
public:
	DAO(wstring path);
	virtual ~DAO();

	void /*vector<Human>*/ find(Human human);

private:
	void create_index(wstring field);
};

/*
	wstring telephone;
	wstring name;
	wstring surname;
	wstring patronymic;
	wstring street;
	int house_num;
	int housing_num;
	int apartment_num;*/
