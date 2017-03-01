#pragma once

#include <string>
#include <vector>

using namespace std;

string getLocalPath();

vector<string> getDirectoryFilenames(string& directoryName);

void createDir(string name);

string getDateAndHour();

void waitForKey();