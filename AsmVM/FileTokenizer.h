#pragma once
#include <vector>
#include <string>

namespace FileTokenizer
{
	typedef std::vector<std::vector<std::string>> TokenizedLines;
	TokenizedLines Tokenize(std::istream &fileName);
}