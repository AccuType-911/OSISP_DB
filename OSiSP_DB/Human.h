#pragma once

#include<string>


using namespace std;


enum HumanFields{TELEPHONE, NAME, SURNAME, PATRONYMIC, STREET, HOUSE_NUM, HOUSING_NUM, APARTMENT_NUM};


class Human
{
public:
	wstring telephone;
	wstring name;
	wstring surname;
	wstring patronymic;
	wstring street;
	int house_num = -1;
	int housing_num = -1;
	int apartment_num = -1;
		
		bool isHumanFiledsAreNOTEmpty() 
		{
			return (this->apartment_num != -1);
		};


	wstring &operator[](HumanFields key) //перегрузка []     
	{
		switch (key) {
		case HumanFields::TELEPHONE:
			return telephone;
		case HumanFields::NAME:
			return name;
		case HumanFields::SURNAME:
			return surname;
		case HumanFields::PATRONYMIC:
			return patronymic;
		case HumanFields::STREET:
			return street;
		case HumanFields::HOUSE_NUM:
			return to_wstring(house_num);
		case HumanFields::HOUSING_NUM:
			return to_wstring(housing_num);
		case HumanFields::APARTMENT_NUM:
			return to_wstring(apartment_num);
		default:
			throw new exception("Such field does not exists!");
		}
	}

};

typedef Human *pHuman;

