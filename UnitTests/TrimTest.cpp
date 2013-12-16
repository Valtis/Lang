#include "stdafx.h"
#include "CppUnitTest.h"
#include "StringUtility.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(TrimTest)
	{
	public:

		TEST_METHOD(StringContainingWhiteSpaceWhenTrimmedIsEmpty)
		{
			string str = "    \r   \n   \t     ";
			str = Utility::Trim(str);
			int length = str.length();
			Assert::AreEqual(0, length);
		}

		TEST_METHOD(EmptyStringTrimmedCorrectly)
		{
			string str = "";
			str = Utility::Trim(str);
			int length = str.length();
			Assert::AreEqual(0, length);
		}

		TEST_METHOD(StringWithNoWhitespaceInBegginningOrEndTrimmedCorrectly)
		{
			string str = "This is a string!";
			str = Utility::Trim(str);
			Assert::AreEqual("This is a string!", str.c_str());
		}

		TEST_METHOD(WhiteSpaceFromBeginningRemovedCorrectly)
		{
			string str = "  This is a string!";
			str = Utility::Trim(str);
			Assert::AreEqual("This is a string!", str.c_str());
		}

		TEST_METHOD(WhiteSpaceFromTheEndRemovedCorrectly)
		{
			string str = "This is a string!  \r \n \t  ";
			str = Utility::Trim(str);
			Assert::AreEqual("This is a string!", str.c_str());
		}

		TEST_METHOD(WhiteSpaceFromTheEndAndTheBeginningRemovedCorrectly)
		{
			string str = "\r   This is a string!  \r \n \t  ";
			str = Utility::Trim(str);
			Assert::AreEqual("This is a string!", str.c_str());
		}
	};
}