#include "stdafx.h"
#include "Lab1MainProject.h"
#include "MovableObject.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

struct WindowRect
{
	int width = 0, height = 0;
};

MovableObjecct *movableObject = new MovableObjecct(0, 0, 100, 100);

bool isMovemovableObject = false;
UINT_PTR timer;
const int TIMER_KEY_RIGHT = 0, TIMER_KEY_LEFT = 1, TIMER_KEY_UP = 2, TIMER_KEY_DOWN = 3;
const int TIMER_WHEEL_UP = 4, TIMER_WHEEL_DOWN = 5;
const int DRAW_TIMER = 0, SPEED_TIMER = 1;
const int TIMER_INTERVAL = 20;
int windowHeight = 0, windowWidth = 0;

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
    LoadStringW(hInstance, IDC_LAB1MAINPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	const auto hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1MAINPROJECT));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return static_cast<int>(msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1MAINPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1MAINPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

WindowRect GetWindowSize(HWND hWnd)
{
	RECT clientRect;
	auto windowWidth = windowHeight = 0;

	if (GetClientRect(hWnd, &clientRect))
	{
		windowWidth = clientRect.right - clientRect.left;
		windowHeight = clientRect.bottom - clientRect.top;
	}

	WindowRect windowRect;

	windowRect.width = windowWidth;
	windowRect.height = windowHeight;

	return windowRect;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

	const auto hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

	const auto rect = GetWindowSize(hWnd);
	movableObject->SetMaxCoordinates(rect.width, rect.height);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   SetTimer(hWnd, DRAW_TIMER, TIMER_INTERVAL, static_cast<TIMERPROC>(nullptr));
   SetTimer(hWnd, SPEED_TIMER, TIMER_INTERVAL, static_cast<TIMERPROC>(nullptr));

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
	        const int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
	        PAINTSTRUCT paintStruct;
	        RECT rect;
		BITMAP bitmap;

	        const auto hDc = BeginPaint(hWnd, &paintStruct);
	        const auto hBitmap = LoadImage(nullptr, L"csharp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

			GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	        const auto hCompatibleDc = CreateCompatibleDC(hDc);
	        const auto hOldBitmap = SelectObject(hCompatibleDc, hBitmap);
			StretchBlt(hDc, movableObject->x1, movableObject->y1, movableObject->x2 - movableObject->x1, movableObject->y2 - movableObject->y1, hCompatibleDc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
			SelectObject(hCompatibleDc, hOldBitmap);
			DeleteObject(hBitmap);
			DeleteDC(hCompatibleDc);
			EndPaint(hWnd, &paintStruct);
        }
        break;
	case WM_SIZE:
		{
		const auto rect = GetWindowSize(hWnd);
		movableObject->SetMaxCoordinates(rect.width, rect.height);
		}
		break;
	case WM_KEYDOWN:
		
		switch (wParam)
		{
		case VK_RIGHT:
			{
			movableObject->toRight = true;
			}
			break;
		case VK_LEFT:
			{
			movableObject->toLeft = true;
			}
			break;
		case VK_DOWN:
			{
			movableObject->toDown = true;
			}
			break;
		case VK_UP:
			{
			movableObject->toUp = true;
			}
			break;
		default: ;
		}
		break;
	case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_RIGHT:
				{
				movableObject->toRight = false;
				}
				break;
			case VK_LEFT:
				{
				movableObject->toLeft = false;
				}
				break;
			case VK_DOWN:
				{
				movableObject->toDown = false;
				}
				break;
			case VK_UP:
				{
				movableObject->toUp = false;
				}
				break;
			default: ;
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			const int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			const int fwKeys = GET_KEYSTATE_WPARAM(wParam);
			if (fwKeys == MK_SHIFT)
			{
				if (zDelta > 0)
				{
					movableObject->horizontalSpeed -= movableObject->acceleration * 2;
				}
				if (zDelta < 0)
				{
					movableObject->horizontalSpeed += movableObject->acceleration * 2;
				}
			}
			else
			{
				if (zDelta > 0)
				{
					movableObject->verticalSpeed -= movableObject->acceleration * 2;
				}
				if (zDelta < 0)
				{
					movableObject->verticalSpeed += movableObject->acceleration * 2;
				}
			}
		}
		break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case DRAW_TIMER:
		{
			movableObject->Draw();
			
			if (movableObject->IsPositionChanged())
			{
				InvalidateRect(hWnd, nullptr, TRUE);
				UpdateWindow(hWnd);
			}
			movableObject->AssignOldValues();
			
		}
		break;
		case SPEED_TIMER:
		{
			movableObject->ProcessKeys();
		}
		break;
		default: ;
		}
	}
		break;
    case WM_DESTROY:
		KillTimer(hWnd, SPEED_TIMER);
		KillTimer(hWnd, DRAW_TIMER);
		free(movableObject);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return static_cast<INT_PTR>(TRUE);

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return static_cast<INT_PTR>(TRUE);
        }
        break;
    default: ;
    }
    return static_cast<INT_PTR>(FALSE);
}
