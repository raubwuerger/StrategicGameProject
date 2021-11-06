#include "stdafx.h"
#include "GameUnitTransportContainerFactory.h"
#include "GameUnitTransportContainer.h"
#include "GameUnit.h"
#include "model\ModelUnitType.h"

GameUnitTransportContainer* GameUnitTransportContainerFactory::Create(const GameUnit* transporter)
{
	GameUnitTransportContainer* newContainer = new GameUnitTransportContainer(transporter);
	newContainer->Capacity = FindCapacity(transporter);
	newContainer->Domain = FindDomain(transporter);
	return newContainer;
}

int GameUnitTransportContainerFactory::FindCapacity(const GameUnit* transporter)
{
	const ModelUnitType* unitType = transporter->GetModelUnitType();
	Q_ASSERT(unitType);
	return unitType->GetTransportCapacityStupid(); //TODO: Sollte eine Transporteinheit verschiedene Einheitentypen (Land,Air,Sea) aufnehmen können, brauche ich hier ein anderes Konzept.
}

QString GameUnitTransportContainerFactory::FindDomain(const GameUnit* transporter)
{
	const ModelUnitType* unitType = transporter->GetModelUnitType();
	Q_ASSERT(unitType);
	return unitType->GetTransportDomainStupid(); //TODO: Sollte eine Transporteinheit verschiedene Einheitentypen (Land,Air,Sea) aufnehmen können, brauche ich hier ein anderes Konzept.
}
