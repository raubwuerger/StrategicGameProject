#include "stdafx.h"
#include "UnitTypeIdSelector.h"

UnitTypeIdSelector::UnitTypeIdSelector(int unitTypeId)
	: UnitTypeId(unitTypeId)
{

}

void UnitTypeIdSelector::SlotTrigger()
{
	emit SignalActiveUnitType(UnitTypeId);
}


