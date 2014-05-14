#include "stdafx.h"
#include "CppUnitTest.h"
#include "DoubleHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestStandardLib
{		
	TEST_CLASS(UnitTestDoubleHelper)
	{
	public:

		TEST_METHOD(Test_Zero)
		{
			Assert::IsTrue( jha::DoubleHelper().IsZero(0.0) );
		}
		TEST_METHOD(Test_Zero2)
		{
			Assert::IsTrue( jha::DoubleHelper().IsZero(0) );
		}
		TEST_METHOD(Test_Zero3)
		{
			Assert::IsTrue( jha::DoubleHelper().IsZero(0.000000000000) );
		}
		TEST_METHOD(Test_ZeroFalse)
		{
			Assert::IsFalse( jha::DoubleHelper().IsZero(0.0000000000001) );
		}
		TEST_METHOD(Test_ZeroFalse2)
		{
			Assert::IsFalse( jha::DoubleHelper().IsZero(-0.0000000000001) );
		}
		TEST_METHOD(Test_ZeroDBL_MIN)
		{
			Assert::IsTrue( jha::DoubleHelper().IsZero(DBL_MIN) );
		}
		TEST_METHOD(Test_ZeroDBL_MAX)
		{
			Assert::IsFalse( jha::DoubleHelper().IsZero(DBL_MAX) );
		}
		TEST_METHOD(Test_Round)
		{
			Assert::IsTrue( jha::DoubleHelper().Round(0.0,0) == 0.0 );
		}
		TEST_METHOD(Test_Round1)
		{
			Assert::IsTrue( jha::DoubleHelper().Round(0.5,0) == 1.0 );
		}
		TEST_METHOD(Test_Round2)
		{
			Assert::IsTrue( jha::DoubleHelper().Round(0.5 + std::numeric_limits<double>::epsilon(),0) == 1.0 );
		}
		TEST_METHOD(Test_Round3)
		{
			Assert::IsTrue( jha::DoubleHelper().Round(0.5 - std::numeric_limits<double>::epsilon(),0) == 0.0 );
		}
		TEST_METHOD(Test_Round4)
		{
			Assert::IsTrue( jha::DoubleHelper().Round(0.05,1) == 0.1 );
		}
		TEST_METHOD(Test_Round5)
		{
			Assert::IsTrue( jha::DoubleHelper().Round(0.05 + std::numeric_limits<double>::epsilon(),1) == 0.10 );
		}
		TEST_METHOD(Test_Round6)
		{
			Assert::IsTrue( jha::DoubleHelper().Round(0.05 - std::numeric_limits<double>::epsilon(),1) == 0.00 );
		}
	};
}