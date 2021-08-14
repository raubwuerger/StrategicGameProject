#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameDemonstrator_TEST
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			bool isEven = 0 % 2;
			isEven = 1 % 2;
			isEven = 2 % 2;
			isEven = 3 % 2;
		}

	};
}