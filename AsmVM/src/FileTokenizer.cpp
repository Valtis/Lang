#include "FileTokenizer.h"
#include "StringUtility.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace FileTokenizer;

TokenizedLines FileTokenizer::Tokenize(istream &file)
{
	TokenizedLines tokenizedLines;
	string line;
	while (getline(file, line))
	{
		line = line.substr(0, line.find(";"));
		auto tokens = Utility::Tokenize(line, " ");

		for (auto t : tokens)
		{
			cout << t << " ";
		}

		tokenizedLines.push_back(tokens);

	}
	return tokenizedLines;
}