#include "stdafx.h"
#include "GameUnitStackingHelper.h"
#include "helper\GameUnitVectorHelper.h"

GameUnitStackingHelper::GameUnitStackingHelper()
	: Selected(nullptr)
{

}

void GameUnitStackingHelper::AddGameUnits(const QVector<const GameUnit*>& gameUnits)
{
	GameUnits = gameUnits;
}

void GameUnitStackingHelper::AddGameUnit( const GameUnit* gameUnit)
{
	GameUnits.push_back(gameUnit);
}

void GameUnitStackingHelper::Clear()
{
	GameUnits.clear();
}

const GameUnit* GameUnitStackingHelper::GetSelected() const
{
	return Selected;
}

void GameUnitStackingHelper::SetSelected(const GameUnit* selected)
{
	Selected = selected;
}

const QVector<const GameUnit*> GameUnitStackingHelper::GetNotSelected()
{
	QVector<const GameUnit*>	notSelected;
	for (int index = 0; index < GameUnits.size(); index++)
	{
		const GameUnit* current = GameUnits.at(index);
		if (current == Selected)
		{
			continue;
		}
		notSelected.push_back(current);
	}
	return notSelected;
}

const GameUnit* GameUnitStackingHelper::Next()
{
	if (0 == GameUnits.size())
	{
		Selected = nullptr;
		return Selected;
	}

	if (1 == GameUnits.size())
	{
		Selected = GameUnits.at(0);
		return Selected;
	}

	if (nullptr == Selected)
	{
		Selected = GameUnits.at(0);
		return Selected;
	}

	//Ab hier 2 Einträge oder mehr!
	GameUnitVectorHelper helper(const_cast<QVector<const GameUnit*>&>(GameUnits));
	int selectedIndex = helper.GetIndex(Selected);

	if (selectedIndex < 0)
	{
		Selected = GameUnits.at(0);
		return Selected;
	}

	//Check for flip to first position
	if ((++selectedIndex) >= GameUnits.size())
	{
		Selected = GameUnits.at(0);
		return Selected;
	}

	Selected = GameUnits.at(selectedIndex);
	return Selected;
}
