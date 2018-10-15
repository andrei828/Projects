#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <direct.h>
#include <cstring>

#include "Manager.h"

using namespace std;

void Display();

Manager * a = new Manager();

int main()
{
	system("Color F0");
	a->SetPath(L"C:\\");
	Display();
}

void Display()
{
	cout << "Current path:" << endl;
	system("cd");
	cout << endl << endl;

	cout << "1) Set path "	               << endl;
	cout << "2) Create file "              << endl;
	cout << "3) Rename file "              << endl;
	cout << "4) Delete file "			   << endl;
	cout << "5) Create folder "            << endl;
	cout << "6) Rename folder "            << endl;
	cout << "7) Delete folder "            << endl;
	cout << "8) Search for files "         << endl;
	cout << "9) See what is in this path " << endl;

	cout << "> ";
	int c;
	cin >> c;

	switch (c) {
	case 1: {
		// set path
		cin.ignore();
		string myStr;
		char path[80];
		cout << "Enter the path: " << endl;
		getline(cin, myStr);
		strncpy(path, myStr.c_str(), sizeof(path));
		path[sizeof(path) - 1] = 0;
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		wchar_t wtext[20];
		mbstowcs(wtext, path, strlen(path) + 1);
		LPWSTR ptr = wtext;
		a->SetPath(wtext);
		Display();
		break;
	}
	case 2: {
		// create file
		char name[20];

		cout << "Enter the name: " << endl;
		cin >> name;
		
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		a->CreateFile(name);
		Display();
		break;
	}
	case 3: {
		// rename file
		char oldname[20];
		char newname[20];

		cout << "Enter the actual name: " << endl;
		cin >> oldname;

		cout << "Enter the new name: " << endl;
		cin >> newname;
		
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		a->RenameFile(oldname, newname);
		Display();
		break;
	}
	case 4: {
		// delete file
		char name[20];

		cout << "Enter the name: " << endl;
		cin >> name;
		
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		a->RemoveFile(name);
		Display();
		break;
	}
	case 5: {
		// create folder
		char name[20];

		cout << "Enter the name: " << endl;
		cin >> name;
		
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		a->CreateFolder(name);
		Display();
		break;
	}
	case 6: {
		// rename folder
		char oldname[20];
		char newname[20];

		cout << "Enter the actual name: " << endl;
		cin >> oldname;

		cout << "Enter the new name: " << endl;
		cin >> newname;
		
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		a->RenameFile(oldname, newname);
		Display();
		break;
	}
	case 7: {
		// delete folder
		char name[20];

		cout << "Enter the name: " << endl;
		cin >> name;
		
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		a->RemoveFolder(name);
		Display();
		break;
	}
	case 8: {
		// search for files
		char name[20];
		char mask[8];

		cout << "Enter the name: " << endl;
		cin >> name;

		cout << "Enter the mask: " << endl;
		cin >> mask;
		
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		a->FindFile(name, mask);
		Display();
		break;
	}
	case 9: {
		cin.ignore();
		system("DIR");
		cout << "Press the enter key to continue" << endl;
		begin:
		char c;
		if (cin.get() != '\n') {
			goto begin;
		}
		
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		Display();
		break;
	}
	}
}
