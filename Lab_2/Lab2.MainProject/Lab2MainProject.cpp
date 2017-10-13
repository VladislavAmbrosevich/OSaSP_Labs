#include "stdafx.h"
#include "Lab2MainProject.h"
#include "PhrasesProvider.h"
#include <locale>
#include <codecvt>
#include <commctrl.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

#define ROW_COUNT 5
#define COLUMN_COUNT 5
int horizontalBorders[COLUMN_COUNT][2];
int verticalBorders[ROW_COUNT][2];

int verticalTab = 0;
int horizontalTab = 2;
int totalHeight = 0;
int verticalShift = 0;
int fontHeight = 0;

RECT clientSize;

PhrasesProvider* phrasesProvider = new PhrasesProvider(11, 11);
auto phrases = phrasesProvider->phrases;

void OnWmPaint(HWND hWnd);
void DrawTable(HDC hDc, bool isDraw);
void PrintPhrases(HDC hDc);
void CalculateHorizontalBorders(int width);
int CalculateVerticalBorders(HDC hDc);
void DrawBorders(HDC hDc);
void FontSizeCalculating(HDC hDc);
int RecalculateVerticalBorders();

HWND htextbox;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2MAINPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2MAINPROJECT));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2MAINPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2MAINPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1000, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void CalculateHorizontalBorders(int width)
{
	const auto step = width / COLUMN_COUNT;
	for (auto i = 0; i < COLUMN_COUNT; i++)
	{
		horizontalBorders[i][0] = i * step;
		horizontalBorders[i][1] = (i + 1) * step;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hWndLV = NULL;

	switch (message)
	{
	case WM_GETMINMAXINFO:
	{
		const auto lpMmi = reinterpret_cast<LPMINMAXINFO>(lParam);
		lpMmi->ptMinTrackSize.x = 300;
		lpMmi->ptMinTrackSize.y = 200;
	}
	break;
	case WM_PAINT:
		OnWmPaint(hWnd);
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &clientSize);
		break;

	case WM_DESTROY:
		free(phrasesProvider);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

void FontSizeCalculating(HDC hDc)
{
	fontHeight = 15;
	verticalTab = 0;
	CalculateHorizontalBorders(clientSize.right - clientSize.left);
	DrawTable(hDc, false);

	while (clientSize.bottom - totalHeight > 10)
	{
		fontHeight++;
		CalculateHorizontalBorders(clientSize.right - clientSize.left);
		DrawTable(hDc, false);
	}

	while (totalHeight > clientSize.bottom)
	{
		fontHeight--;
		CalculateHorizontalBorders(clientSize.right - clientSize.left);
		DrawTable(hDc, false);
	}

	while (clientSize.bottom - totalHeight > ROW_COUNT + 5)
	{
		totalHeight = RecalculateVerticalBorders();
		verticalTab++;
	}
	

	DrawTable(hDc, true);
}

void OnWmPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	RECT clientRect;

	const auto hDc = BeginPaint(hWnd, &ps);
	const auto color = RGB(0, 0, 0);
	const auto pen = CreatePen(PS_SOLID, 1, color);
	SelectObject(hDc, pen);
	

	FontSizeCalculating(hDc);

	DeleteObject(hDc);
	EndPaint(hWnd, &ps);
}

int RecalculateVerticalBorders()
{
	int counter = 1;
	auto totalHeight = 0;
	for (auto i = 0; i < ROW_COUNT; i++)
	{
		if (i > 0)
		{
			verticalBorders[i][0] += counter - 1;
		}
		verticalBorders[i][1] += counter;
		
		counter++;
	}
	totalHeight += verticalBorders[ROW_COUNT - 1][1];

	return totalHeight;
}

void DrawTable(HDC hDc, bool isDraw)
{
	auto font = CreateFont(fontHeight, 0, 0, 0, FW_NORMAL, false, false, false, 0, 0, 0, 0, 0, nullptr);
	SelectObject(hDc, font);
	

	if (isDraw)
	{
		PrintPhrases(hDc);
		DrawBorders(hDc);
	}
	else
	{
		totalHeight = CalculateVerticalBorders(hDc);
	}
	DeleteObject(font);
}


int CalculateVerticalBorders(HDC hDc)
{
	RECT rect;
	rect.top = 0;

	auto totalHeight = 0;
	verticalBorders[0][0] = 0;
	for (auto i = 0; i < ROW_COUNT; i++)
	{
		if (i > 0)
		{
			verticalBorders[i][0] = verticalBorders[i - 1][1];
		}
		auto rowMaxHeight = 0;
		for (auto j = 0; j < COLUMN_COUNT; j++)
		{
			rect.bottom = INT_MAX;
			rect.left = horizontalBorders[j][0];
			rect.right = horizontalBorders[j][1];
			DrawText(hDc, phrases[i][j].c_str(), -1, &rect, DT_CALCRECT | DT_WORDBREAK | DT_WORD_ELLIPSIS);
			rowMaxHeight = max(rowMaxHeight, rect.bottom);
		}
		totalHeight += rowMaxHeight;
		if (i > 0)
		{
			verticalBorders[i][1] = verticalBorders[i - 1][1] + rowMaxHeight;
		}
		else
		{
			verticalBorders[0][1] = rowMaxHeight;
		}
	}
	return totalHeight;
}

void PrintPhrases(HDC hDc)
{
	RECT rect;

	for (auto i = 0; i < ROW_COUNT; i++)
	{
		for (auto j = 0; j < COLUMN_COUNT; j++)
		{
			rect.top = verticalBorders[i][0] + verticalTab / 2;
			rect.bottom = verticalBorders[i][1];
			rect.left = horizontalBorders[j][0];
			rect.right = horizontalBorders[j][1];
			DrawText(hDc, phrases[i][j].c_str(), -1, &rect, DT_WORDBREAK | DT_WORD_ELLIPSIS);
		}
	}
}

void DrawBorders(HDC hDc)
{
	for (auto i = 0; i < ROW_COUNT - 1; i++)
	{
		MoveToEx(hDc, clientSize.left, verticalBorders[i][1], nullptr);
		LineTo(hDc, clientSize.right, verticalBorders[i][1]);
	}
	for (auto i = 0; i < COLUMN_COUNT - 1; i++)
	{
		MoveToEx(hDc, horizontalBorders[i][1] - horizontalTab, 0, nullptr);
		LineTo(hDc, horizontalBorders[i][1] - horizontalTab, clientSize.bottom);
	}
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}