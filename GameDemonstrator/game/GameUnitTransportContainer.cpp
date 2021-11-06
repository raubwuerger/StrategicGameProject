#include "stdafx.h"
#include "GameUnitTransportContainer.h"
#include "helper\GameUnitVectorHelper.h"

GameUnitTransportContainer::GameUnitTransportContainer()
	: Transporter(nullptr),
	Domain(NOT_INITIALIZED_STRING),
	Capacity(NOT_INITIALIZED_INT)
{

}

GameUnitTransportContainer::GameUnitTransportContainer(const GameUnit* transporter)
	: Transporter(transporter),
	Domain(NOT_INITIALIZED_STRING),
	Capacity(NOT_INITIALIZED_INT)
{
	Q_ASSERT(transporter);
}

bool GameUnitTransportContainer::GetIsValid() const
{
	if (nullptr == Transporter)
	{
		return false;
	}

	if (true == Domain.isEmpty())
	{
		return false;
	}

	return Capacity > 0;
}

int GameUnitTransportContainer::GetCount() const
{
	return TransportedUnits.size();
}

int GameUnitTransportContainer::GetCapacity() const
{
	return Capacity;
}

const QString& GameUnitTransportContainer::GetDomain() const
{
	return Domain;
}

bool GameUnitTransportContainer::EmbarkUnit(GameUnit* toEmbark)
{
	Q_ASSERT(toEmbark);
	if (TransportedUnits.size() >= Capacity)
	{
		Q_ASSERT(false);
		return false;
	}
	TransportedUnits.push_back(toEmbark);
	return true;
}

bool GameUnitTransportContainer::DisembarkUnit(GameUnit* toDisembark)
{
	GameUnitVectorHelper helper(TransportedUnits);
	return helper.Remove(toDisembark) == nullptr ? false : true;
}

bool GameUnitTransportContainer::GetFreeCapacity() const
{
	return (Capacity - GetCount()) > 0;
}

GameUnit* GameUnitTransportContainer::GetAt(int index)
{
	if (index > TransportedUnits.size())
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return TransportedUnits.at(index);
}

