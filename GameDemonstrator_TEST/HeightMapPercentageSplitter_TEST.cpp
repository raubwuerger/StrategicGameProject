#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestFiles\HeightMapPercentageSplitter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameDemonstrator_TEST
{
	std::vector<float> emptyValues;
	std::vector<float> zeroValues = { 0.0 };
	std::vector<float> manyValues = { -1.0, -0.5, 0.0, 0.5, 1.0 };
	std::vector<float> aLotOfValues;

	float RandomFloat(float min, float max)
	{
		// this  function assumes max > min, you may want 
		// more robust error checking for a non-debug build
		float random = ((float)rand()) / (float)RAND_MAX;

		// generate (in your case) a float between 0 and (4.5-.78)
		// then add .78, giving you a float between .78 and 4.5
		float range = max - min;
		return (random*range) + min;
	}

	std::vector<float> CreateVectorWithItems( int itemCount )
	{
		std::vector<float> manyItems;
		for (int i = 0; i < itemCount; i++)
		{
			manyItems.push_back(RandomFloat(-2.0,2.0));
		}
		return manyItems;
	}

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

		TEST_METHOD(PercentageValueTwice)
		{
			HeightMapPercentageSplitter splitter;
			if (false == splitter.RegisterPercentageValue(50))
			{
				Assert::Fail(reinterpret_cast<const wchar_t*>("Should fail!"));
			}
			if (true == splitter.RegisterPercentageValue(50))
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

		TEST_METHOD(ValuesManyPercentageOne)
		{
			HeightMapPercentageSplitter splitter;
			if (false == splitter.RegisterPercentageValue(50))
			{
				Assert::Fail(reinterpret_cast<const wchar_t*>("Should fail!"));
			}
			std::map<int, std::vector<float> > result;
			result = splitter.CalculatePercentageValue(manyValues);
		}

		TEST_METHOD(ValuesManyPercentageTwo)
		{
			HeightMapPercentageSplitter splitter;
			splitter.RegisterPercentageValue(50);
			splitter.RegisterPercentageValue(90);
			std::map<int, std::vector<float> > result;
			result = splitter.CalculatePercentageValue(manyValues);
		}

		TEST_METHOD(ValuesManyPercentageToMany)
		{
			HeightMapPercentageSplitter splitter;
			splitter.RegisterPercentageValue(10);
			splitter.RegisterPercentageValue(20);
			splitter.RegisterPercentageValue(30);
			splitter.RegisterPercentageValue(40);
			splitter.RegisterPercentageValue(90);
			std::map<int, std::vector<float> > result;
			result = splitter.CalculatePercentageValue(manyValues);
			Assert::IsTrue(result.empty());
		}

		TEST_METHOD(ValuesManyPercentage4)
		{
			HeightMapPercentageSplitter splitter;
			splitter.RegisterPercentageValue(20);
			splitter.RegisterPercentageValue(40);
			splitter.RegisterPercentageValue(60);
			splitter.RegisterPercentageValue(80);
			std::map<int, std::vector<float> > result;
			result = splitter.CalculatePercentageValue(manyValues);
			unsigned int destCount = 5;
			Assert::AreEqual(result.size(), destCount);
		}

		TEST_METHOD(ValuesaLotOfValues)
		{
			HeightMapPercentageSplitter splitter;
			if (false == splitter.RegisterPercentageValue(50))
			{
				Assert::Fail(reinterpret_cast<const wchar_t*>("Should fail!"));
			}

			aLotOfValues = CreateVectorWithItems(10000);
			std::map<int, std::vector<float> > result;
			result = splitter.CalculatePercentageValue(aLotOfValues);
		}
	};
}