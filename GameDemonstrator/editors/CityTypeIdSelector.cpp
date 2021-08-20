#include "stdafx.h"
#include "CityTypeIdSelector.h"

CityTypeIdSelector::CityTypeIdSelector(int CityTypeId)
	: CityTypeId(CityTypeId)
{

}

void CityTypeIdSelector::SlotTrigger()
{
	emit SignalCityTypeActive(CityTypeId);
}
