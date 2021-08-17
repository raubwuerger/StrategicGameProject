#include "stdafx.h"
#include "OwnerTypeIdSelector.h"

OwnerTypeIdSelector::OwnerTypeIdSelector(int ownerTypeId)
	: OwnerTypeId(ownerTypeId)
{

}

void OwnerTypeIdSelector::SlotTrigger()
{
	emit SignalOwnerTypeActive(OwnerTypeId);
}
