#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestFiles\HeightMapPercentageSplitter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameDemonstrator_TEST
{
	std::vector<float> emptyValues;
	std::vector<float> zeroValues = { 0.0 };
	std::vector<float> manyValues = { -1.0, -0.5, 0.0, 0.5, 1.0 };

	TEST_CLASS(HeightMapPercentageSplitter_TEST)
	{
	public:

		TEST_METHOD(PercentageValueLesser1)
		{
			HeightMapPercentageSplitter splitter;
			if (true == splitter.RegisterPercentageValue(0))
			{
				Assert::Fail(reinterpret_cast<const wchar_t*>("Should fail!"));
			}
		}

		TEST_METHOD(PercentageValueGreater100)
		{
			HeightMapPercentageSplitter splitter;
			if (true == splitter.RegisterPercentageValue(101))
			{
				Assert::Fail(reinterpret_cast<const wchar_t*>("Should fail!"));
			}
		}

		TEST_METHOD(ValuesEMPTY)
		{
			HeightMapPercentageSplitter splitter;
			if (false == splitter.RegisterPercentageValue(50))
			{
				Assert::Fail(reinterpret_cast<const wchar_t*>("Should fail!"));
			}
			std::map<int, std::vector<float> > result;
			result = splitter.CalculatePercentageValue(zeroValues);
		}

		TEST_METHOD(ValuesMany)
		{
			HeightMapPercentageSplitter splitter;
			if (false == splitter.RegisterPercentageValue(50))
			{
				Assert::Fail(reinterpret_cast<const wchar_t*>("Should fail!"));
			}
			std::map<int, std::vector<float> > result;
			result = splitter.CalculatePercentageValue(manyValues);
		}
	};
}