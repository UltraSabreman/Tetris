#ifndef _UTILS_H_
#define _UTILS_H_
#include "Includes.h"

class Utilities
{
	public:
		template <class Type>
		static Type subtractVectors(Type *vec2, Type *vec1)
		{
			Type tempVec;

			for (int i = 0; i < vec1->size(); i++)
			{
				bool inBoth = false;
				for (int l = 0; l < vec2->size(); l++)
				{
					if (vec1->at(i) == vec2->at(l))
					{
						inBoth = true;
						break;
					}
				}

				if (!inBoth)
					tempVec.push_back(vec1->at(i));
			}

			return tempVec;
		}

		static void stringExplode(string input, char delim, vector<string> &output)
		{
			if(!output.empty()) output.clear();
			int charInd = 0;
			string tempString = "";

			while ((unsigned int) charInd <= input.length())
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
};


#endif