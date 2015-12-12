#pragma once
#include "Human.h"
#include <vector>
#include <string>

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

class Parser
{
	#define BUFFER_SIZE 1024

public:
	class iterator;

                	
	long get_db_size();			
	iterator get_iterator(); 	
	long get_db_size();			// גמחנאשאוע נאחלונ פאיכא
	Parser(wstring path);
	~Parser();

	
	vector<Human> fetchHumansObjects_FromFile() {
		
	}


private:
	wstring file_path;











public:
	class iterator
	{
	public:
		typedef iterator self_type;
		typedef Human value_type;
		typedef Human& reference;
		typedef Human* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;

		iterator(HANDLE hMapFile) {
			//this->ptr = ptr;
			this->hMapFile = hMapFile;
			this->ptr = (wchar_t*)MapViewOfFile(hMapFile,   // handle to map object
				FILE_MAP_ALL_ACCESS, // read/write permission
				0,
				0,
				BUFFER_SIZE);

			if (this->ptr == NULL)
			{
				_tprintf(TEXT("Could not map view of file (%d).\n"),
					GetLastError());

				CloseHandle(hMapFile);

				return;
			}
		}

		self_type operator++() {
			self_type i = *this;

			while (has_next()) 
			{
				
			}
			
			return i;
		}
		pointer operator->() {
			return ptr_;
		}
		

		bool has_next();
	private:
		pointer ptr_;
		WCHAR *ptr;
		HANDLE hMapFile;
		bool is_EOF;

		Human* getHuman() 
		{
			
		}
	};

};

