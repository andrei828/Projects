#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <fstream>
#include <cstring>
#include <Windows.h>
using namespace std;

class Manager
{
public:

	Manager();
	~Manager();

	void SetPath(LPCWSTR p);
	void CreateFile(const char * name);
	void RemoveFile(const char * name);
	void RenameFile(const char * oldname, const char * newname);
	void CreateFolder(const char * name);
	void RemoveFolder(const char * name);
	void FindFile(char * name, const char * mask);

	LPCWSTR GetP();
	char * GetPath();

private:

	char * path;
	LPCWSTR p;

};