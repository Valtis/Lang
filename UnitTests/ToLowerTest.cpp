#include "stdafx.h"
#include "CppUnitTest.h"
#include "StringUtility.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTests
{
	TEST_CLASS(ToLowerTest)
	{
	public:

		TEST_METHOD(ToLowerWorksOnEmptyString)
		{
			string str = "";
			Utility::ToLower(str);
			int length = str.length();
			Assert::AreEqual(0, length);
		}

		TEST_METHOD(ToLowerWorks)
		{                
			string str = "ThisContainsmiXEDLettersanDNumbers12AsWel##lasSpecialCharacters  and White space   ";
			Utility::ToLower(str);
			Assert::AreEqual("thiscontainsmixedlettersandnumbers12aswel##lasspecialcharacters  and white space   ",
				str.c_str());
		}
	};
}