#include "win.h"

#include <Windows.h>
#include <direct.h>

string getLocalPath()
{
	string path;
	char buf[100];
	int bytes = GetModuleFileName(NULL, buf, 100);
	for (int i = 0; i<bytes; i++)
		path += buf[i];
	int pos = (int)path.rfind("\\");
	path = path.substr(0, pos + 1);
	return path;
}

vector<string> getDirectoryFilenames(string& directoryName)
{
	vector<string> filenames;
	string searchExpression = directoryName + "\\*.*";
	WIN32_FIND_DATA fileAttributes;
	int result;
	HANDLE handleFile = ::FindFirstFile(searchExpression.c_str(), &fileAttributes);
	if (handleFile != INVALID_HANDLE_VALUE)
	{
		do {
			if (!(fileAttributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				filenames.push_back(fileAttributes.cFileName);
			}
			result = ::FindNextFile(handleFile, &fileAttributes);
		} while (result != 0);
		::FindClose(handleFile);
	}
	return filenames;
}

void createDir(string name)
{
	_mkdir(name.c_str());
}
