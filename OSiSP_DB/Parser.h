#pragma once
#include "Human.h"
#include <vector>
#include <string>

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <wchar.h>

#include <iostream>
#include <sstream>



class Parser
{


public:
	class iterator;

                	
	long get_db_size();			
	iterator get_iterator(); 	
//	long get_db_size();			// גמחנאשאוע נאחלונ פאיכא
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

		iterator(HANDLE hFile) {
			//this->ptr = ptr;
			this->hFile = hFile;

			this->hMapFile = CreateFileMapping(hFile,
				NULL,
				PAGE_READONLY,
				0,
				0,
				NULL);

			fileSize = GetFileSize(hFile, &tempFileSize);
			fileSize += (((__int64)tempFileSize) << 32);

			tempFileSize = fileSize;

			CloseHandle(hFile);

			GetSystemInfo(&sysInfo);
		}
		void mapViewNewPartOfFile() 
		{
			countOfMappingBytes = sysInfo.dwAllocationGranularity;
			if (tempFileSize < sysInfo.dwAllocationGranularity)
			{
				countOfMappingBytes = tempFileSize;
			}

			this->ptr = (wchar_t*)MapViewOfFile(this->hMapFile, FILE_MAP_READ, (DWORD)(fileOffset >> 32), (DWORD)(fileOffset & 0xFFFFFFFF), countOfMappingBytes);


			if (this->ptr == NULL)
			{
				this->is_EOF = true;

				CloseHandle(hMapFile);
				return;
			}

		}
		void unmapViewPreviousPartOfFile()
		{
			currentPositionInBuffer = 0;
			fileOffset += countOfMappingBytes;
			tempFileSize -= countOfMappingBytes;
			UnmapViewOfFile(this->ptr);
		}

		self_type operator++() {
			self_type i = *this;

			if (has_next()) 
			{
				this->currentHuman = getNext();
			}
			
			return i;
		}

		void begin() 
		{
			 fileOffset = 0;
			 countOfMappingBytes = 0;
			 currentPositionInBuffer = 0;
			 
			 loadSecondPartOfFileInMemory();
		}

		bool is_end()
		{
			return is_EOF;
		}

		pointer operator->() {
			return ptr_;
		}
		
		std::vector<Human *> fetchAllHumansFromFile() 
		{
			std::vector<Human *> vectorOfHumans;
			
			begin();

			Human *currentHuman;
			while (!this->is_end()) {
				currentHuman = getNext();

				if (currentHuman != NULL) vectorOfHumans.push_back(currentHuman);
			}

			return vectorOfHumans;
		}

		bool has_next() {

			if (currentPositionInBuffer < countOfMappingBytes) {
				return true;
			} else {
				loadSecondPartOfFileInMemory();

				if (this->ptr != NULL && currentPositionInBuffer < countOfMappingBytes)
					return true;
				else
					return false;
			}
			
			return false;
		}

		Human* getNext() 
		{
			Human *human = new Human();

			char *arr;
			std::wstring line;
			bool isFileEmpty = false;

				do
				{
					wchar_t symbol = this->ptr[currentPositionInBuffer];
					
					line.push_back(symbol);

					currentPositionInBuffer++;	
					if (currentPositionInBuffer >= countOfMappingBytes / 2) { 
						if (!loadSecondPartOfFileInMemory()) {
							is_EOF = true;
							this->currentHuman = NULL;

							return NULL;
						}
					}
				
				} while (this->ptr[currentPositionInBuffer] != '\n');

				currentPositionInBuffer++;

				std::vector<std::wstring> vectorOfValeus = parseBuffer(line);
				int numberOfParameter = 0;
				
				for (auto attack = vectorOfValeus.begin(); attack != vectorOfValeus.end(); ++attack)
				{
					switch (numberOfParameter)
					{
						case 0:
							human->telephone = vectorOfValeus[0];
						break;

						case 1:
							human->surname = vectorOfValeus[1];
							break;

						case 2:
							human->name = vectorOfValeus[2];
							break;

						case 3:
							human->patronymic = vectorOfValeus[3];
							break;

						case 4:
							human->street = vectorOfValeus[4];
							break;

						case 5:
							try
							{
								human->house_num = std::stoi(vectorOfValeus[5]);
							}
							catch (exception exc) {
								human->house_num = 0;
							}

							break;

						case 6:
							try
							{
								human->housing_num = std::stoi(vectorOfValeus[6]);
							}
							catch (exception exc) {
								human->housing_num = 0;
							}
							break;
						case 7:
						    try
							{
								human->apartment_num = std::stoi(vectorOfValeus[7]);
							} catch (exception exc) {
								human->apartment_num = 0;
							}
							break;
					}
					
					numberOfParameter++;
				}

			line.clear();
			this->currentHuman = human;

			return human;
		}

		std::vector<std::wstring> parseBuffer(std::wstring tempString)
		{
				std::vector<std::wstring> vectorInfo = Split(tempString, L';');
				tempString.clear();
			
				return vectorInfo;
		}
		std::vector<std::wstring> Split(const std::wstring &subscriberInfo, wchar_t delimiter)
		{

			std::vector<std::wstring> tempSubscInfo;
			std::wstringstream stream(subscriberInfo);
			std::wstring item;
			while (getline(stream, item, delimiter)) {
				tempSubscInfo.push_back(item);
			}
			return tempSubscInfo;
		}

		bool loadSecondPartOfFileInMemory() 
		{
			unmapViewPreviousPartOfFile();
			mapViewNewPartOfFile();
			
			return (countOfMappingBytes > 0) && (this->ptr != NULL);
		}

		Human* getHuman()
		{
			return currentHuman;
		}

	private:
		SYSTEM_INFO sysInfo; // System info for getting size of mapping file in RAM.
		
		DWORD tempFileSize; //base file size
		__int64 fileSize; //help var.
		__int64 fileOffset = 0;

		DWORD countOfMappingBytes;

		Human *currentHuman;
		char *arrayOfSymbols;

		pointer ptr_;
		WCHAR *ptr;
		HANDLE hMapFile;
		HANDLE hFile;

		int currentPositionInBuffer = 0;
		bool is_EOF;
	};

};

