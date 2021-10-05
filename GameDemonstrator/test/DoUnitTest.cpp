#include "stdafx.h"
#include "DoUnitTest.h"
#include "StringToBoolConverter_TEST.h"

void DoUnitTest::DoTests()
{
	StringToBoolConverter();
}

bool DoUnitTest::StringToBoolConverter()
{
	StringToBoolConverter_TEST test;
	test.Test();
	return true;
}
