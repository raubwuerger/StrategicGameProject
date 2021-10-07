#ifndef MAPHEXITEMSETTING_H
#define MAPHEXITEMSETTING_H

struct MapHexItemSetting
{
	MapHexItemSetting()
		: ShowId(true),
		ShowColAndRow(true),
		ShowCoordinates(false),
		ShowTextBorder(false),
		ShowText(true),
		DrawHexBorder(true)
	{
	}

	MapHexItemSetting(const MapHexItemSetting& rhs)
		: ShowId(rhs.ShowId),
		ShowColAndRow(rhs.ShowColAndRow),
		ShowCoordinates(rhs.ShowCoordinates),
		ShowTextBorder(rhs.ShowTextBorder),
		ShowText(rhs.ShowText),
		DrawHexBorder(rhs.DrawHexBorder)
	{

	}
public:
	bool	ShowId;
	bool	ShowColAndRow;
	bool	ShowCoordinates;
	bool	ShowTextBorder;
	bool	ShowText;
	bool	DrawHexBorder;

};

#endif // MAPHEXITEMSETTING_H