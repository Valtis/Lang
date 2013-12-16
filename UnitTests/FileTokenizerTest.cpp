#include "stdafx.h"
#include "CppUnitTest.h"
#include "FileTokenizer.h"
#include <string>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(FileTokenizerTests)
	{
	public:

		TEST_METHOD(SingleLineTokenCountCorrectWhenEmptyLine)
		{
			stringstream stream;
			stream << "          ";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			int lineCnt = out.size();
			Assert::AreEqual(0, lineCnt);
		}

		TEST_METHOD(SingleLineTokenCountCorrectWhenEmptyLineAndCommentInTheMiddle)
		{
			stringstream stream;
			stream << "       ; this space intentionally left blank";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			int lineCnt = out.size();
			Assert::AreEqual(0, lineCnt);
		}

		TEST_METHOD(SingleLineTokenCountCorrect)
		{
			stringstream stream;
			stream << "This is a single line";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			int lineCnt = out.size();
			Assert::AreEqual(1, lineCnt);
			int tokenCnt = out[0].size();

			Assert::AreEqual(5, tokenCnt);

		}

		TEST_METHOD(SingleLineTokensCorrect)
		{
			stringstream stream;
			stream << "This is a single line";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			Assert::AreEqual("This", out[0][0].c_str());
			Assert::AreEqual("is", out[0][1].c_str());
			Assert::AreEqual("a", out[0][2].c_str());
			Assert::AreEqual("single", out[0][3].c_str());
			Assert::AreEqual("line", out[0][4].c_str());
		}

		TEST_METHOD(SingleLineTokenCountCorrectStartsWithComment)
		{
			stringstream stream;
			stream << "; This is a single commented line";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			int lineCnt = out.size();
			Assert::AreEqual(0, lineCnt);
		}

		TEST_METHOD(SingleLineTokenCountWhenEndCommented)
		{
			stringstream stream;
			stream << "This is a single line;and this part is commented";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			int lineCnt = out.size();
			Assert::AreEqual(1, lineCnt);
			int tokenCnt = out[0].size();

			Assert::AreEqual(5, tokenCnt);

		}

		TEST_METHOD(SingleLineTokensCorrectWhenEndCommented)
		{
			stringstream stream;
			stream << "This is a single line;and this part is commented";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			Assert::AreEqual("This", out[0][0].c_str());
			Assert::AreEqual("is", out[0][1].c_str());
			Assert::AreEqual("a", out[0][2].c_str());
			Assert::AreEqual("single", out[0][3].c_str());
			Assert::AreEqual("line", out[0][4].c_str());
		}

		TEST_METHOD(MultipleLinesTokenCountCorrect)
		{
			stringstream stream;
			stream << "This is the first line\nand this is second line with more text";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			int lineCnt = out.size();
			Assert::AreEqual(2, lineCnt);
			int tokenCntFirstLine = out[0].size();
			int tokenCntSecondLine = out[1].size();

			Assert::AreEqual(5, tokenCntFirstLine);
			Assert::AreEqual(8, tokenCntSecondLine);
		}

		TEST_METHOD(MultipleLinesTokensCorrect)
		{
			stringstream stream;
			stream << "This is the first line\nand this is second line with more text";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			Assert::AreEqual("This", out[0][0].c_str());
			Assert::AreEqual("is", out[0][1].c_str());
			Assert::AreEqual("the", out[0][2].c_str());
			Assert::AreEqual("first", out[0][3].c_str());
			Assert::AreEqual("line", out[0][4].c_str());

			Assert::AreEqual("and", out[1][0].c_str());
			Assert::AreEqual("this", out[1][1].c_str());
			Assert::AreEqual("is", out[1][2].c_str());
			Assert::AreEqual("second", out[1][3].c_str());
			Assert::AreEqual("line", out[1][4].c_str());
			Assert::AreEqual("with", out[1][5].c_str());
			Assert::AreEqual("more", out[1][6].c_str());
			Assert::AreEqual("text", out[1][7].c_str());
		}

		TEST_METHOD(MultipleLinesTokenCountCorrectWhenOneLineCommentedOut)
		{
			stringstream stream;
			stream << "This is the first line\n;this line is commented\nand this is second line with more text";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			int lineCnt = out.size();
			Assert::AreEqual(2, lineCnt);
			int tokenCntFirstLine = out[0].size();
			int tokenCntSecondLine = out[1].size();

			Assert::AreEqual(5, tokenCntFirstLine);
			Assert::AreEqual(8, tokenCntSecondLine);
		}

		TEST_METHOD(MultipleLinesTokensCorrectWhenOneLineCommentedOut)
		{
			stringstream stream;
			stream << "This is the first line\n;this line is commented\nand this is second line with more text";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			Assert::AreEqual("This", out[0][0].c_str());
			Assert::AreEqual("is", out[0][1].c_str());
			Assert::AreEqual("the", out[0][2].c_str());
			Assert::AreEqual("first", out[0][3].c_str());
			Assert::AreEqual("line", out[0][4].c_str());

			Assert::AreEqual("and", out[1][0].c_str());
			Assert::AreEqual("this", out[1][1].c_str());
			Assert::AreEqual("is", out[1][2].c_str());
			Assert::AreEqual("second", out[1][3].c_str());
			Assert::AreEqual("line", out[1][4].c_str());
			Assert::AreEqual("with", out[1][5].c_str());
			Assert::AreEqual("more", out[1][6].c_str());
			Assert::AreEqual("text", out[1][7].c_str());
		}

		TEST_METHOD(MultipleLinesTokenCountCorrectWhenOneLineCommentedOutInTheEnd)
		{
			stringstream stream;
			stream << "This is the first line\nSecond line here;this part is commented\nand this is third line with more text";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			int lineCnt = out.size();
			Assert::AreEqual(3, lineCnt);
			int tokenCntFirstLine = out[0].size();
			int tokenCntSecondLine = out[1].size();
			int tokenCntThirdLine = out[2].size();
			
			Assert::AreEqual(5, tokenCntFirstLine);
			Assert::AreEqual(3, tokenCntSecondLine);
			Assert::AreEqual(8, tokenCntThirdLine);
		}

		TEST_METHOD(MultipleLinesTokensCorrectWhenOneLineCommentedOutInTheEnd)
		{
			stringstream stream;
			stream << "This is the first line\nSecond line here;this part is commented\nand this is third line with more text";

			vector<vector<string>> out = FileTokenizer::Tokenize(stream);
			Assert::AreEqual("This", out[0][0].c_str());
			Assert::AreEqual("is", out[0][1].c_str());
			Assert::AreEqual("the", out[0][2].c_str());
			Assert::AreEqual("first", out[0][3].c_str());
			Assert::AreEqual("line", out[0][4].c_str());

			Assert::AreEqual("Second", out[1][0].c_str());
			Assert::AreEqual("line", out[1][1].c_str());
			Assert::AreEqual("here", out[1][2].c_str());

			Assert::AreEqual("and", out[2][0].c_str());
			Assert::AreEqual("this", out[2][1].c_str());
			Assert::AreEqual("is", out[2][2].c_str());
			Assert::AreEqual("third", out[2][3].c_str());
			Assert::AreEqual("line", out[2][4].c_str());
			Assert::AreEqual("with", out[2][5].c_str());
			Assert::AreEqual("more", out[2][6].c_str());
			Assert::AreEqual("text", out[2][7].c_str());
		}


	};
}