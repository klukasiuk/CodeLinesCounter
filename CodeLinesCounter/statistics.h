#pragma once

#include <string>

using std::string;

// Structures for organizing data

struct expansionStatistic																	// Struct for organizing data about one file expansions
{
	string expansion;

	int numberOfFiles;

	int numberOfBlankLines;

	int numberOfBracketLines;

	int numberOfCodeLines;

	int numberOfComments;

	expansionStatistic()
	{
		numberOfFiles = 0;
		numberOfBlankLines = 0;
		numberOfBracketLines = 0;
		numberOfCodeLines = 0;
		numberOfComments = 0;
	}
};

struct fileStatistic																		// Struct for organizing data about specific file
{
	string filename;

	string expansion;

	int numberOfFiles;

	int numberOfBlankLines;

	int numberOfBracketLines;

	int numberOfCodeLines;

	int numberOfComments;

	fileStatistic()
	{
		numberOfFiles = 0;
		numberOfBlankLines = 0;
		numberOfBracketLines = 0;
		numberOfCodeLines = 0;
		numberOfComments = 0;
	}
};


// Tests for type of line

bool isBlankLine(string line);

bool isBracketLine(string line);

bool isThereComment(string line);