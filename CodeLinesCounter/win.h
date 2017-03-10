#pragma once

#include <string>
#include <vector>

using namespace std;

string getLocalPath();													// Return path for folder containing this program

vector<string> getDirectoryFilenames(string& directoryName);			// Lists all files in given folder

void createDir(string name);											// Creates new dir in local dir