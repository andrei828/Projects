#include "Manager.h"

Manager::Manager()
{
	path = nullptr;
}

Manager::~Manager()
{
	delete path;
}

void Manager::SetPath(LPCWSTR p)
{
	if (!SetCurrentDirectory(p)) {
		this->p = p;
	}
}

void Manager::CreateFile(const char * name)
{
	string p = path;
	string n = name;
	p += n;
	fstream newfile;
	newfile.open(p, ios::app);

	if (newfile.is_open()) {
		cout << "File created successfully" << endl;
		newfile << "";
		newfile.close();
	}
	else {
		cout << "There was an error to open the file from " << path << endl;
	}
}

void Manager::RemoveFile(const char * name)
{
	char * copypath = this->path;
	int newsize = strlen(copypath) + strlen(name);

	char * command = new char(newsize);

	strcpy(command, copypath);
	strcat(command, name);
		
	if (remove(command) == 0) {
		cout << "File deleted successfully" << endl;
	}
	else {
		cout << "There was an error deleting the file" << endl;
	}
}

void Manager::RenameFile(const char * oldname, const char * newname)
{
	char * copypath = this->path;
	int newsize1 = strlen(copypath) + strlen(oldname);
	int newsize2 = strlen(copypath) + strlen(newname);

	char * command1 = new char(newsize1);
	char * command2 = new char(newsize2);

	strcpy(command1, copypath);
	strcpy(command2, copypath);

	strcat(command1, oldname);
	strcat(command1, newname);

	if (rename(command1, command2 ) == 0) {
		cout << "File renamed successfully" << endl;
	}
	else {
		cout << "There was a problem renaming the file" << endl;
	}
}

void Manager::CreateFolder(const char * name)
{
	char * copypath = this->path;
	int newsize = strlen(copypath) + strlen(name);

	char * command = new char(newsize);

	strcpy(command, copypath);
	strcat(command, name);
	
	if (_mkdir(command) == 0) {
		cout << "Folder created successfully" << endl;
	}
	else {
		cout << "There was an error creating the folder" << endl;
	}
}

void Manager::RemoveFolder(const char * name)
{
	char * copypath = this->path;
	int newsize = strlen(copypath) + strlen(name);

	char * command = new char(newsize);

	strcpy(command, copypath);
	strcat(command, name);

	if (_rmdir(command) == 0) {
		cout << "Folder deleted successfully" << endl;
	}
	else {
		cout << "There was an error deleting the folder" << endl;
	}

}

void Manager::FindFile(char * name, const char * mask)
{
	char * copypath = this->path;
	int newsize = strlen(copypath) + strlen(name) + strlen(mask);

	char * fullinfo = new char(newsize);

	strcpy(fullinfo, copypath);
	strcat(name, mask);
	strcat(fullinfo, name);

	_finddata_t * fileinfo = new _finddata_t;
	
	long done = _findfirst(fullinfo, fileinfo);

	int MayWeWork = done;
	int count = 0;

	while (MayWeWork != -1) {
		count++;
		cout << fileinfo->name << "endl";
		MayWeWork = _findnext(done, fileinfo);
	}

	cout << endl << "Information: found " << count << " file(s) in folder: " << fullinfo << endl;
}

LPCWSTR Manager::GetP()
{
	return p;
}

char * Manager::GetPath()
{
	return path;
}