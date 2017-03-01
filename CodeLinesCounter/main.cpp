#include <iostream>
#include <fstream>

#include "win.h"

using namespace std;

struct expansionStatistic
{
	string expansion;

	int numberOfFiles;

	int numberOfLines;

	expansionStatistic()
	{
		numberOfLines = numberOfFiles = 0;
	}
};

int main()
{
	vector<string> SupportedExpansions;

	SupportedExpansions.push_back(string(".cpp"));
	SupportedExpansions.push_back(string(".c"));
	SupportedExpansions.push_back(string(".h"));
	SupportedExpansions.push_back(string(".glsl"));

	vector<expansionStatistic> ExpansionsStat;

	string folderPath;

	cout << "Do you want to write path to other folder (default is current folder) ?\n";
	cout << "(y/n) -> ";

	char choose;

	cin >> choose;
	cin.sync();

	if (choose == 'y')
	{
		cout << "Write folder path \n";
		cout << "Path -> ";

		cin >> folderPath;

	}
	else
	{
		folderPath = getLocalPath();
	}


	vector<string> filenames = getDirectoryFilenames(folderPath);

	cout << "\nFound " << filenames.size() << " files\n";

	for (int i = 0; i < filenames.size(); i++)
	{
		string filename = filenames[i];

		int pos = filename.find(".");

		string expansion = filename.substr(pos, filename.size() - pos);

		bool isFileSupported = false;

		for (int a = 0; a < SupportedExpansions.size(); a++)
		if (expansion == SupportedExpansions[a])
		isFileSupported = true;

		if (isFileSupported == false)
		{
			cout << "\nFile : " << filename << " is not supported \n";
			continue;
		}

		ifstream FileStream((folderPath + filename).c_str());

		if (FileStream.is_open() == false)
		{
			cout << "\n Cannot open file :" << filename << "\n";
			continue;
		}

		string line;

		int numberOfLines = 0;

		while (getline(FileStream, line))
		{
			if (line.size() > 5)
			numberOfLines++;
		}

		bool isThereThatExpansion = false;
		int expIndex = -1;

		for (int b = 0; b < ExpansionsStat.size(); b++)
		if (ExpansionsStat[b].expansion == expansion)
		{
			isThereThatExpansion = true;
			expIndex = b;
		}

		if (isThereThatExpansion == false)
		{
			expansionStatistic statistic;

			statistic.expansion = expansion;

			ExpansionsStat.push_back(statistic);

			expIndex = ExpansionsStat.size() - 1;
		}

		ExpansionsStat[expIndex].numberOfFiles++;
		ExpansionsStat[expIndex].numberOfLines += numberOfLines;

		FileStream.close();
	}

	int allLines = 0;
	int allFiles = 0;

	for (int b = 0; b < ExpansionsStat.size(); b++)
	{
		allLines += ExpansionsStat[b].numberOfLines;
		allFiles += ExpansionsStat[b].numberOfFiles;
	}

	ofstream resultFile(("CodeLinesCounter_Result_"+ getDateAndHour() + ".txt").c_str());
	
	if (resultFile.is_open() == false)
	{
		cout << "\n Cannot open file for result saving";
		return -1;
	}

	resultFile << "CodeLinesCounter\n\n";
	resultFile << getDateAndHour() << "\n\n";

	resultFile << "OVERALL RESULT\n\n";
	resultFile << "Files found : "<<allFiles<<"\n";
	resultFile << "All lines of code : " << allLines << "\n\n";

	resultFile << "DETAILED RESULT \n\n";

	for (int i = 0; i < ExpansionsStat.size(); i++)
	{
		resultFile << "Expansion : " << ExpansionsStat[i].expansion << "\n";
		resultFile << "Files : " << ExpansionsStat[i].numberOfFiles << "\n";
		resultFile << "Lines of code : " << ExpansionsStat[i].numberOfLines << "\n\n";
	}

	resultFile.close();

	cout << "\nAll done :)";

	waitForKey();

	return 0;
}