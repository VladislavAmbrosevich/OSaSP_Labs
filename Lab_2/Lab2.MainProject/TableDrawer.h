#pragma once
#include "PhrasesProvider.h"

class TableDrawer
{
	const int _horizontalTab = 2;

	RECT _clientSize;
	TStringsMatrix _phrases;
	int _fontHeight = 0, _verticalTab = 0, _totalHeight = 0;
	int _rowCount = 0, _columnCount = 0;
	int _horizontalBorders[11][2];
	int _verticalBorders[11][2];

	void PrintPhrases(HDC hDc);
	void DrawBorders(HDC hDc);
	void DrawTable(HDC hDc, bool isDraw);
	int RecalculateVerticalBorders();
	void CalculateHorizontalBorders();
	int CalculateVerticalBorders(HDC hDc);

public:
	TableDrawer(int rowCount, int columnCount, TStringsMatrix phrases);

	void RefreshTable(HDC hDc);
	void SetClientSize(RECT clientSize);
};
