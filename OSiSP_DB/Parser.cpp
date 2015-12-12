#include "stdafx.h"
#include <string>
#include "Parser.h"


Parser::Parser(wstring path)
{
	this->file_path = path;
}

Parser::~Parser()
{

}


Parser::iterator Parser::get_iterator()
{
	HANDLE hMapFile;
	wchar_t *pBuf;

	hMapFile = CreateFileMappingW(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUFFER_SIZE,                // maximum object size (low-order DWORD)
		this->file_path.c_str());                 // name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not create file mapping object (%d).\n"),
			GetLastError());
		return;
	}

	Parser::iterator it(hMapFile);
	return it;

	//CopyMemory((PVOID)pBuf, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
	//_getch();

//	UnmapViewOfFile(pBuf);
//	CloseHandle(hMapFile);
}

//iterator<Human> get_iterator(); 	5 laba
long get_db_size() { return -1; }
