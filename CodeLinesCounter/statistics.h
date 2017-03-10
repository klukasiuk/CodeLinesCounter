#pragma once

#include <string>

using std::string;


struct expansionStatistic																	// Struct for organizing data about different file expansions
{
	string expansion;

	int numberOfFiles;

	int numberOfLines;

	expansionStatistic()
	{
		numberOfLines = numberOfFiles = 0;
	}
};

struct fileStatistic																		// Struct for organizing data about specific file
{
	string filename;

	string expansion;

	int numberOfLines;

	fileStatistic()
	{
		numberOfLines = 0;
	}
};