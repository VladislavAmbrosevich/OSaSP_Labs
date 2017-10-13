#include "stdafx.h"
#include "PhrasesProvider.h"

PhrasesProvider::PhrasesProvider(int rows, int columns)
{
	if (rows > maxRows)
	{
		_rows = maxRows;
	}
	else
	{
		_rows = rows;
	}
	if (columns > maxColumns)
	{
		_columns = maxColumns;
	}
	else
	{
		_columns = columns;
	}

	auto phrasesRow = std::vector<std::wstring>();
	phrasesRow.push_back(L"This is the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the rat,");
	phrasesRow.push_back(L"That ate the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the cat,");
	phrasesRow.push_back(L"That killed the rat,");
	phrasesRow.push_back(L"That ate the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the dog,");
	phrasesRow.push_back(L"That worried the cat,");
	phrasesRow.push_back(L"That killed the rat,");
	phrasesRow.push_back(L"That ate the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the cow with the crumpled horn,");
	phrasesRow.push_back(L"That tossed the dog,");
	phrasesRow.push_back(L"That worried the cat,");
	phrasesRow.push_back(L"That killed the rat,");
	phrasesRow.push_back(L"That ate the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the maiden all forlorn,");
	phrasesRow.push_back(L"That milked the cow with the crumpled horn,");
	phrasesRow.push_back(L"That tossed the dog,");
	phrasesRow.push_back(L"That worried the cat,");
	phrasesRow.push_back(L"That killed the rat,");
	phrasesRow.push_back(L"That ate the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the man all tattered and torn,");
	phrasesRow.push_back(L"That kissed the maiden all forlorn,");
	phrasesRow.push_back(L"That milked the cow with the crumpled horn,");
	phrasesRow.push_back(L"That tossed the dog,");
	phrasesRow.push_back(L"That worried the cat,");
	phrasesRow.push_back(L"That killed the rat,");
	phrasesRow.push_back(L"That ate the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the priest all shaven and shorn,");
	phrasesRow.push_back(L"That married the man all tattered and torn,");
	phrasesRow.push_back(L"That kissed the maiden all forlorn,");
	phrasesRow.push_back(L"That milked the cow with the crumpled horn,");
	phrasesRow.push_back(L"That tossed the dog,");
	phrasesRow.push_back(L"That worried the cat,");
	phrasesRow.push_back(L"That killed the rat,");
	phrasesRow.push_back(L"That ate the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the cock that crowed in the morn,");
	phrasesRow.push_back(L"That waked the priest all shaven and shorn,");
	phrasesRow.push_back(L"That married the man all tattered and torn,");
	phrasesRow.push_back(L"That kissed the maiden all forlorn,");
	phrasesRow.push_back(L"That milked the cow with the crumpled horn,");
	phrasesRow.push_back(L"That tossed the dog,");
	phrasesRow.push_back(L"That worried the cat,");
	phrasesRow.push_back(L"That killed the rat,");
	phrasesRow.push_back(L"That ate the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrasesRow.push_back(_emptyString);
	phrases.push_back(phrasesRow);

	phrasesRow.clear();
	phrasesRow.push_back(L"This is the farmer sowing his corn,");
	phrasesRow.push_back(L"That kept the cock that crowed in the morn,");
	phrasesRow.push_back(L"That waked the priest all shaven and shorn,");
	phrasesRow.push_back(L"That married the man all tattered and torn,");
	phrasesRow.push_back(L"That kissed the maiden all forlorn,");
	phrasesRow.push_back(L"That milked the cow with the crumpled horn,");
	phrasesRow.push_back(L"That tossed the dog,");
	phrasesRow.push_back(L"That worried the cat,");
	phrasesRow.push_back(L"That killed the rat,");
	phrasesRow.push_back(L"That ate the malt");
	phrasesRow.push_back(L"That lay in the house that Jack built.");
	phrases.push_back(phrasesRow);
}
