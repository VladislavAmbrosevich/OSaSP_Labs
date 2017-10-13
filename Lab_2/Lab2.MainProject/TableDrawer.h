#pragma once

class TableDrawer
{
	const int _horizontalTab = 2;


	RECT _clientSize;
	int _fontHeight = 0, _verticalTab = 0, _totalHeight = 0;
	int _rowCount = 0, _columnCount = 0;

	void PrintPhrases(HDC hDc);
	void DrawBorders(HDC hDc);
	void DrawTable(HDC hDc, bool isDraw);
	int RecalculateVerticalBorders();

public:
	TableDrawer(int rowCount, int columnCount);

	void CalculateTableParams(HDC hDc);
	void SetClientSize(RECT clientSize);
};