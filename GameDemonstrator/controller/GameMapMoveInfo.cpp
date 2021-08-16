#include "stdafx.h"
#include "GameMapMoveInfo.h"
#include "LogInterface.h"
#include "map/MapHexItem.h"
#include "map/MapHexItemRepository.h"
#include "map/MapUnitItem.h"

QMap<int, QSize> GameMapMoveInfo::MovementTypeColumEven;
QMap<int, QSize> GameMapMoveInfo::MovementTypeColumOdd;

void GameMapMoveInfo::CreateMovementTypes()
{
	MovementTypeColumEven.insert(7, QSize(-1, -1));
	MovementTypeColumEven.insert(8, QSize(-1, 0));
	MovementTypeColumEven.insert(9, QSize(-1, 1));
	MovementTypeColumEven.insert(1, QSize(0, -1));
	MovementTypeColumEven.insert(2, QSize(+1, 0));
	MovementTypeColumEven.insert(3, QSize(0, +1));

	MovementTypeColumOdd.insert(7, QSize(0, -1));
	MovementTypeColumOdd.insert(8, QSize(-1, 0));
	MovementTypeColumOdd.insert(9, QSize(0, 1));
	MovementTypeColumOdd.insert(1, QSize(+1, -1));
	MovementTypeColumOdd.insert(2, QSize(+1, 0));
	MovementTypeColumOdd.insert(3, QSize(+1, +1));
}

GameMapMoveInfo::GameMapMoveInfo(const MapUnitItem* source)
	: SourceMapUnitItem(source),
	SourceMapHexItem(nullptr)
{

}

const MapHexItem* GameMapMoveInfo::GetDestinationInfo(int movementDirection) const
{
	if (false == MovementTypeColumEven.contains(movementDirection) || false == MovementTypeColumOdd.contains(movementDirection))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Invalid movement direction %1").arg(QString::number(movementDirection)));
		return nullptr;
	}

	SourceMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(SourceMapUnitItem->GetMapHexItemId());
	if (nullptr == SourceMapHexItem)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("MapHexItem with id=%1 not found!").arg(QString::number(SourceMapUnitItem->GetMapHexItemId())));
		return nullptr;
	}
	
	QSize offset = GetCorrectOffset(movementDirection, SourceMapHexItem);

	const QSize source(SourceMapHexItem->GetRow(), SourceMapHexItem->GetCol());
	QSize destination = source + offset;
	const MapHexItem* destinationMapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemByRowCol(destination.width(), destination.height());
	if (nullptr == destinationMapHexItem)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Destination MapHexItem [row|col]=%1|%2 not found!").arg(QString::number(destination.width())).arg(QString::number(destination.height())));
		return nullptr;
	}

	return destinationMapHexItem;
}

QSize GameMapMoveInfo::GetCorrectOffset(int movementDirection, const MapHexItem* mapHexItem) const
{
	int isEvenInt = mapHexItem->GetCol() % 2;
	if (0 == isEvenInt)
	{
		return MovementTypeColumEven[movementDirection];
	}

	return MovementTypeColumOdd[movementDirection];
}

