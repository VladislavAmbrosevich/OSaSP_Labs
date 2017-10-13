#include "stdafx.h"
#include "TableDrawer.h"

TableDrawer::TableDrawer(int rowCount, int columnCount, TStringsMatrix phrases)
{
	_rowCount = rowCount;
	_columnCount = columnCount;
	_phrases = phrases;
}


void TableDrawer::SetClientSize(RECT clientSize)
{
	_clientSize.bottom = clientSize.bottom;
	_clientSize.top = clientSize.top;
	_clientSize.left = clientSize.left;
	_clientSize.right = clientSize.right;
}

void TableDrawer::RefreshTable(HDC hDc)
{
	_fontHeight = 15;
	_verticalTab = 0;
	CalculateHorizontalBorders();
	DrawTable(hDc, false);

	while (_clientSize.bottom - _totalHeight > 10)
	{
		_fontHeight++;
		CalculateHorizontalBorders();
		DrawTable(hDc, false);
	}

	while (_totalHeight > _clientSize.bottom)
	{
		_fontHeight--;
		CalculateHorizontalBorders();
		DrawTable(hDc, false);
	}

	while (_clientSize.bottom - _totalHeight > _rowCount + 5)
	{
		_totalHeight = RecalculateVerticalBorders();
		_verticalTab++;
	}

	DrawTable(hDc, true);
}


void TableDrawer::CalculateHorizontalBorders()
{
	const auto step = (_clientSize.right - _clientSize.left) / _columnCount;
	for (auto i = 0; i < _columnCount; i++)
	{
		_horizontalBorders[i][0] = i * step;
		_horizontalBorders[i][1] = (i + 1) * step;
	}
}

void TableDrawer::DrawBorders(HDC hDc)
{
	for (auto i = 0; i < _rowCount - 1; i++)
	{
		MoveToEx(hDc, _clientSize.left, _verticalBorders[i][1], nullptr);
		LineTo(hDc, _clientSize.right, _verticalBorders[i][1]);
	}
	for (auto i = 0; i < _columnCount - 1; i++)
	{
		MoveToEx(hDc, _horizontalBorders[i][1] - _horizontalTab, 0, nullptr);
		LineTo(hDc, _horizontalBorders[i][1] - _horizontalTab, _clientSize.bottom);
	}
}

void TableDrawer::PrintPhrases(HDC hDc)
{
	RECT rect;

	for (auto i = 0; i < _rowCount; i++)
	{
		for (auto j = 0; j < _columnCount; j++)
		{
			rect.top = _verticalBorders[i][0] + _verticalTab / 2;
			rect.bottom = _verticalBorders[i][1];
			rect.left = _horizontalBorders[j][0];
			rect.right = _horizontalBorders[j][1];
			DrawText(hDc, _phrases[i][j].c_str(), -1, &rect, DT_WORDBREAK | DT_WORD_ELLIPSIS);
		}
	}
}

int TableDrawer::RecalculateVerticalBorders()
{
	auto counter = 1;
	auto totalHeight = 0;
	for (auto i = 0; i < _rowCount; i++)
	{
		if (i > 0)
		{
			_verticalBorders[i][0] += counter - 1;
		}
		_verticalBorders[i][1] += counter;

		counter++;
	}
	totalHeight += _verticalBorders[_rowCount - 1][1];

	return totalHeight;
}

void TableDrawer::DrawTable(HDC hDc, bool isDraw)
{
	auto font = CreateFont(_fontHeight, 0, 0, 0, FW_NORMAL, false, false, false, 0, 0, 0, 0, 0, nullptr);
	SelectObject(hDc, font);

	if (isDraw)
	{
		PrintPhrases(hDc);
		DrawBorders(hDc);
	}
	else
	{
		_totalHeight = CalculateVerticalBorders(hDc);
	}
	DeleteObject(font);
}

int TableDrawer::CalculateVerticalBorders(HDC hDc)
{
	RECT rect;
	rect.top = 0;

	auto totalHeight = 0;
	_verticalBorders[0][0] = 0;
	for (auto i = 0; i < _rowCount; i++)
	{
		if (i > 0)
		{
			_verticalBorders[i][0] = _verticalBorders[i - 1][1];
		}
		auto rowMaxHeight = 0;
		for (auto j = 0; j < _columnCount; j++)
		{
			rect.bottom = INT_MAX;
			rect.left = _horizontalBorders[j][0];
			rect.right = _horizontalBorders[j][1];
			DrawText(hDc, _phrases[i][j].c_str(), -1, &rect, DT_CALCRECT | DT_WORDBREAK | DT_WORD_ELLIPSIS);
			rowMaxHeight = max(rowMaxHeight, rect.bottom);
		}
		totalHeight += rowMaxHeight;
		if (i > 0)
		{
			_verticalBorders[i][1] = _verticalBorders[i - 1][1] + rowMaxHeight;
		}
		else
		{
			_verticalBorders[0][1] = rowMaxHeight;
		}
	}
	return totalHeight;
}
