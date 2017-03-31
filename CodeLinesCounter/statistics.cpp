#include "statistics.h"

#include <iostream>

bool isBlankLine(string line)
{
	if (line.size() == 0)						// If there is no character in line
	return true;

	for (int i = 0; i < line.size(); i++)
	{
		if ((int)line.at(i) > 32)				// If there is any printed character
		return false;
	}

	return true;
}

bool isBracketLine(string line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (line.at(i) == '{' || line.at(i) == '}')				// If there is bracket in line
		return true;
	}

	return false;
}

bool isThereComment(string line)
{
	int index = line.find("//");

	if (index < 0)
	{
		index = line.find("/*");

		if (index < 0)
			return false;
		
		return true;
	}

	return true;
}
