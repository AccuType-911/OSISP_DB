#pragma once
#include "Human.h"
#include <vector>
#include <string>

class Parser
{
	vector<Human> fetchHumansObjects_FromFile();
                	
	long get_db_size();			
	//iterator<Human> get_iterator(); 	
	long get_db_size();			// גמחנאשאוע נאחלונ פאיכא

public:
	Parser(wstring path);
	~Parser();
	
private:
	wstring file_path;
};

