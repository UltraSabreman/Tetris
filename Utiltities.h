#include "Includes.h"

void stringExplode(string input, char delim, vector<string> &output)
{
	if(!output.empty()) output.clear();
	int charInd = 0;
	string tempString = "";

	while (charInd <= input.length())
	{
		char tempChar = input[charInd];

		if(tempChar == delim)
		{
			output.push_back(tempString);
			tempString = "";
		}else
			tempString += input[charInd];
		charInd++;
	}
	output.push_back(tempString); //for the last part that doesn't hvae a delim
}