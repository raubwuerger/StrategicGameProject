#include "stdafx.h"
#include "GameUnitTransportContainer.h"
#include "helper\GameUnitVectorHelper.h"
#include "helper\GameUnitStackingHelper.h"

GameUnitTransportContainer::GameUnitTransportContainer()
	: Transporter(nullptr),
	Domain(NOT_INITIALIZED_STRING),
	Capacity(NOT_INITIALIZED_INT),
	GameUnitStackingHelperObject(nullptr)
{
	GameUnitStackingHelperObject = new GameUnitStackingHelper;
}

GameUnitTransportContainer::GameUnitTransportContainer(const GameUnit* transporter)
	: Transporter(transporter),
	Domain(NOT_INITIALIZED_STRING),
	Capacity(NOT_INITIALIZED_INT)
{
	Q_ASSERT(transporter);
	GameUnitStackingHelperObject = new GameUnitStackingHelper;
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

	UpdateStackingHelper();

	return true;
}

void GameUnitTransportContainer::UpdateStackingHelper()
{
	const GameUnit* selected = GameUnitStackingHelperObject->GetSelected();
	GameUnitStackingHelperObject->Clear();
	GameUnitStackingHelperObject->AddGameUnits(TransportedUnits);
	GameUnitStackingHelperObject->AddGameUnit(Transporter);
	GameUnitStackingHelperObject->SetSelected(selected);
}

bool GameUnitTransportContainer::DisembarkUnit(GameUnit* toDisembark)
{
	GameUnitVectorHelper helper(TransportedUnits);
	if (false == (helper.Remove(toDisembark) == nullptr ? false : true))
	{
		return false;
	}

	UpdateStackingHelper();
	return true;
}

bool GameUnitTransportContainer::GetFreeCapacity() const
{
	return (Capacity - GetCount()) > 0;
}

const GameUnit* GameUnitTransportContainer::GetAt(int index)
{
	if (index > TransportedUnits.size())
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return TransportedUnits.at(index);
}

const GameUnit* GameUnitTransportContainer::GetSelectedUnit()
{
	return GameUnitStackingHelperObject->GetSelected();
}

const GameUnit* GameUnitTransportContainer::SelectNextUnit()
{
	return GameUnitStackingHelperObject->Next();
}

const QVector<const GameUnit*> GameUnitTransportContainer::GetNotSelectedUnits()
{
	return GameUnitStackingHelperObject->GetNotSelected();
}

