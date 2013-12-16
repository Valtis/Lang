#include "stdafx.h"
#include "CppUnitTest.h"
#include "StringUtility.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{		
	TEST_CLASS(TokenizerTests)
	{
	public:

		TEST_METHOD(OutputSizeCorrectEmpty)
		{
			string str = "";
			vector<string> out = Utility::Tokenize(str, " ");
			int size = out.size();
			Assert::AreEqual(0, size);
		}
		
		TEST_METHOD(OutputSizeCorrectSimple)
		{
			string str = "This is a string";
			vector<string> out = Utility::Tokenize(str, " ");
			int size = out.size();
			Assert::AreEqual(4, size);
		}

		TEST_METHOD(OutputValuesCorrectSimple)
		{
			string str = "This is a string";
			vector<string> out = Utility::Tokenize(str, " ");
			
			Assert::AreEqual("This", out[0].c_str());
			Assert::AreEqual("is", out[1].c_str());
			Assert::AreEqual("a", out[2].c_str());
			Assert::AreEqual("string", out[3].c_str());
		}

		TEST_METHOD(OutputSizeCorrectMultipleSpaces)
		{
			string str = "This    is a string    ";
			vector<string> out = Utility::Tokenize(str, " ");
			int size = out.size();
			Assert::AreEqual(4, size);
		}

		TEST_METHOD(OutputValuesCorrectMultipleSpaces)
		{
			string str = "This    is a string    ";
			vector<string> out = Utility::Tokenize(str, " ");

			Assert::AreEqual("This", out[0].c_str());
			Assert::AreEqual("is", out[1].c_str());
			Assert::AreEqual("a", out[2].c_str());
			Assert::AreEqual("string", out[3].c_str());
		}

		TEST_METHOD(OutputSizeCorrectComplex)
		{
			string str = "This;is*a string";
			vector<string> out = Utility::Tokenize(str, " ;*");
			int size = out.size();
			Assert::AreEqual(4, size);
		}

		TEST_METHOD(OutputValuesCorrectComplex)
		{
			string str = "This;is*a string";
			vector<string> out = Utility::Tokenize(str, " ;*");

			Assert::AreEqual("This", out[0].c_str());
			Assert::AreEqual("is", out[1].c_str());
			Assert::AreEqual("a", out[2].c_str());
			Assert::AreEqual("string", out[3].c_str());
		}

	};
}