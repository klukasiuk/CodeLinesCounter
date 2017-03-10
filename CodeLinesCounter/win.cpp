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

	HANDLE handleFile = FindFirstFile(searchExpression.c_str(), &fileAttributes);

	if (handleFile != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if (!(fileAttributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
			filenames.push_back(fileAttributes.cFileName);

			result = FindNextFile(handleFile, &fileAttributes);
		} 
		while (result != 0);

		FindClose(handleFile);
	}

	return filenames;
}

vector<string> getSubDirectories(string& directoryName)
{
	vector<string> subdirs;

	string searchExpression = directoryName + "\\*.*";

	WIN32_FIND_DATA fileAttributes;

	int result;

	HANDLE handleFile = FindFirstFile(searchExpression.c_str(), &fileAttributes);

	if (handleFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (fileAttributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				subdirs.push_back(fileAttributes.cFileName);

			result = FindNextFile(handleFile, &fileAttributes);
		} while (result != 0);

		FindClose(handleFile);
	}


	subdirs.erase(subdirs.begin());
	subdirs.erase(subdirs.begin());

	return subdirs;
}

vector<string> getFilesRecursively(string & directoryName, int level)
{
	if(level > 5)					// Dont go to deep in recursion
	return vector<string>();

	vector<string> filenames;
	vector<string> filenamesFromSubdir;
	vector<string> subdirs;

	filenames = getDirectoryFilenames(directoryName);
	subdirs = getSubDirectories(directoryName);

	for (int i = 0; i < subdirs.size(); i++)
	{
		filenamesFromSubdir = getFilesRecursively(directoryName + "\\" + subdirs[i], level + 1);

		for (int a = 0; a < filenamesFromSubdir.size(); a++)
		filenames.push_back(subdirs[i] + "\\" + filenamesFromSubdir[a]);
	}

	return filenames;
}

void createDir(string name)
{
	_mkdir(name.c_str());
}
