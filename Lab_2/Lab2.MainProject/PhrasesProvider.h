#pragma once
#include <vector>
#include <string>

#define MAX_ROWS 11;
#define MAX_COLUMNS 11;
#define EMPTY_STRING L"";

typedef std::vector<std::vector<std::wstring>> TStringsMatrix;

class PhrasesProvider
{
	int _rows = 0, _columns = 0;
	std::wstring _emptyString = EMPTY_STRING;

//	TStringsMatrix GetRandomNumberPhrases();

public:
	TStringsMatrix phrases;
	int maxRows = MAX_ROWS;
	int maxColumns = MAX_COLUMNS;

	PhrasesProvider(int rows, int columns);
};
