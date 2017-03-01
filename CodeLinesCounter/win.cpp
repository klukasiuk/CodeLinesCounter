#include "win.h"

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <direct.h>
#include <time.h>
#include <chrono>

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

// Returns string with actual time
string getHour()
{
	string s;

	time_t rawtime;
	tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	int hour = timeinfo.tm_hour;
	int min = timeinfo.tm_min;
	int sec = timeinfo.tm_sec;

	if (hour < 10)
		s += "0" + std::to_string(hour) + ".";
	else
		s += std::to_string(hour) + ".";

	if (min < 10)
		s += "0" + std::to_string(min) + ".";
	else
		s += std::to_string(min) + ".";

	if (sec < 10)
		s += "0" + std::to_string(sec);
	else
		s += std::to_string(sec);


	return s;
}

// Returns string with actual time
string getDate()
{
	string s;

	time_t rawtime;
	tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	int year = timeinfo.tm_year + 1900;
	int day = timeinfo.tm_mday;
	int month = timeinfo.tm_mon + 1;

	s += std::to_string(year) + ".";

	if (month < 10)
		s += "0" + std::to_string(month) + ".";
	else
		s += std::to_string(month) + ".";

	if (day < 10)
		s += "0" + std::to_string(day);
	else
		s += std::to_string(day);

	return s;
}

string getDateAndHour()
{
	string s = getDate() + "_" + getHour();

	return s;
}

void waitForKey()
{
	cin.sync();
	std::getchar();
	std::getchar();
}
