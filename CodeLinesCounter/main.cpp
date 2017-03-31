#include <iostream>						// For text input/output
#include <fstream>						// For handling files

#include "win.h"						// Some system dependent utilities
#include "utilities.h"					// Some utilities like getting time
#include "statistics.h"					// Structs for creating file statistics

using namespace std;					// Dont care about namespaces in such small project


// GLOBALS


// CONST PARAMETERS

const int MinNumberOfCharsForCodeLine = 5;													// How many chars must be in line to be counted as line of code

// GLOBAL CONTAINERS

vector<string> SupportedExpansions;															// Here we put all expansions that we want to be calculated

vector<expansionStatistic> ExpansionsStat;													// Vector for combined data

vector<fileStatistic> FileStat;																// Vector for specific data about every file

// GLOBAL PATHS

string folderPath;																			// Directory containing project

vector<string> filenames;																	// Listed files from folderPath directory


// Functions


void init()
{
	// Expansion initialization

	SupportedExpansions.push_back(string(".cpp"));														// For example few c++ expansions
	SupportedExpansions.push_back(string(".c"));
	SupportedExpansions.push_back(string(".h"));
	SupportedExpansions.push_back(string(".glsl"));

	// Getting folder with project

	cout << "Do you want to give path to other folder (default is current folder) ?\n";					// Let the user choose folder
	cout << "(y/n) -> ";

	string choose;

	cin >> choose;

	if (choose == "y" || choose == "Y" || choose == "yes" || choose == "Yes")
	{
		cout << "\n";
		cout << "Write folder path \n";
		cout << "Path -> ";

		cin >> folderPath;

		cout << "\n";
	}
	else
	{
		folderPath = getLocalPath();																	// Get from windows folder with this program
	}

	// Listing files

	vector<string> subdirs = getSubDirectoriesRecursively(folderPath);

	cout << "Found subdirectories :\n\n";

	for (int i = 0; i < subdirs.size(); i++)
		cout << subdirs[i] << "\n";

	filenames = getFilesRecursively(folderPath);														// Get from windows all filenames in this folder

	cout << "\n\nFound " << filenames.size() << " files\n";
}

void processFiles()
{
	for (int i = 0; i < filenames.size(); i++)															// For every found file
	{
		string filename = filenames[i];

		int pos = filename.find(".");

		if (pos < 0)																					// In case of file without extension (linux style)
			continue;

		string expansion = filename.substr(pos, filename.size() - pos);									// Extract expansion

		bool isFileSupported = false;

		for (int a = 0; a < SupportedExpansions.size(); a++)
			if (expansion == SupportedExpansions[a])
			{
				isFileSupported = true;
				break;
			}

		if (isFileSupported == false)																	// If we dont like this expansion continue loop
		{
			cout << "\nFile : " << filename << " is not supported \n";
			continue;
		}

		fileStatistic newFile;

		newFile.filename = filename;
		newFile.expansion = expansion;

		ifstream FileStream((folderPath + "\\" + filename).c_str());											// Lets open file

		if (FileStream.is_open() == false)																// Checking if file was opened correctly
		{
			cout << "\n Cannot open file : " << filename << "\n";
			continue;
		}

		string line;

		while (getline(FileStream, line))																// For every line in file
		{
			if (isBlankLine(line))
			newFile.numberOfBlankLines++;

			if (isBracketLine(line))
			newFile.numberOfBracketLines++;

			if (isThereComment(line))
			newFile.numberOfComments++;


			if (line.size() > MinNumberOfCharsForCodeLine)												// Check if line have enough chars to be considered
			newFile.numberOfCodeLines++;
		}

		bool isThereThatExpansion = false;
		int expIndex = -1;

		for (int b = 0; b < ExpansionsStat.size(); b++)													// Check if we already have files with that expansion
			if (ExpansionsStat[b].expansion == expansion)
			{
				isThereThatExpansion = true;
				expIndex = b;
			}

		if (isThereThatExpansion == false)																// If not create new category
		{
			expansionStatistic statistic;

			statistic.expansion = expansion;

			ExpansionsStat.push_back(statistic);

			expIndex = ExpansionsStat.size() - 1;
		}

		ExpansionsStat[expIndex].numberOfFiles++;														// Add data to category
		ExpansionsStat[expIndex].numberOfCodeLines += newFile.numberOfCodeLines;
		ExpansionsStat[expIndex].numberOfBlankLines += newFile.numberOfBlankLines;
		ExpansionsStat[expIndex].numberOfBracketLines += newFile.numberOfBracketLines;
		ExpansionsStat[expIndex].numberOfComments += newFile.numberOfComments;

		FileStat.push_back(newFile);																	// Add this file to summary

		FileStream.close();																				// Close file
	}

}

void printResults()
{
	int allLines = 0;
	int allFiles = 0;

	for (int b = 0; b < ExpansionsStat.size(); b++)														// Calculating overall result
	{
		allLines += ExpansionsStat[b].numberOfCodeLines;
		allFiles += ExpansionsStat[b].numberOfFiles;
	}

	ofstream resultFile(("CodeLinesCounter_Result_" + getDateAndHour() + ".txt").c_str());				// Open file with current date

	if (resultFile.is_open() == false)
	{
		cout << "\n Cannot open file for result saving\n";

		waitForKey();
		exit(EXIT_FAILURE);
	}

	resultFile << "CodeLinesCounter v0.9\n\n";
	resultFile << getDateAndHour() << "\n\n";

	resultFile << "OVERALL RESULT\n\n";
	resultFile << "Files found : " << allFiles << "\n";
	resultFile << "All lines of code : " << allLines << "\n\n";

	resultFile << "DETAILED RESULT \n\n";

	for (int i = 0; i < ExpansionsStat.size(); i++)														// Print results
	{
		resultFile << "Expansion : " << ExpansionsStat[i].expansion << "\n";
		resultFile << "Files : " << ExpansionsStat[i].numberOfFiles << "\n";
		resultFile << "Lines of code : " << ExpansionsStat[i].numberOfCodeLines << "\n";
		resultFile << "Blank lines : " << ExpansionsStat[i].numberOfBlankLines << "\n";
		resultFile << "Bracket lines : " << ExpansionsStat[i].numberOfBracketLines << "\n";
		resultFile << "Comments  : " << ExpansionsStat[i].numberOfComments << "\n\n";
	}

	resultFile.close();																					// Close file

	cout << "\nAll done :)";

	waitForKey();																						// Let user check for errors
}

void release()
{


}


int main()
{
	init();

	processFiles();

	printResults();

	release();

	return 0;
}