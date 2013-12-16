#include "FileTokenizer.h"
#include "StringUtility.h"
#include <fstream>
#include <iostream>
#include "Tokens.h"
using namespace std;
using namespace FileTokenizer;

TokenizedLines FileTokenizer::Tokenize(istream &file)
{
	TokenizedLines tokenizedLines;
	string line;
	while (getline(file, line))
	{
		line = Utility::Trim(line);
		line = line.substr(0, line.find(COMMENT_TOKEN));
		if (line.empty())
		{
			continue;
		}

		auto tokens = Utility::Tokenize(line, " ");

		for (auto t : tokens)
		{
			cout << t << " ";
		}

		tokenizedLines.push_back(tokens);

	}
	return tokenizedLines;
}