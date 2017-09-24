#include "stdafx.h"
#include "Lab1MainProject.h"


#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

class Ellipce
{
	public:
		int x1, y1, x2, y2;
		int acceleration = 0;
		bool toRight = false, toLeft = false, toDown = false, toUp = false;
		bool isBrake = false;
		
		int verticalSpeed = 0, horizontalSpeed = 0;
		int braking = 1;
		int step = 2;
		int maxRight = 0, maxDown = 0;


	Ellipce(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	public:
		void ProcessKeys()
		{
			if (toRight)
			{
				horizontalSpeed += step;
			}
			if (toLeft)
			{
				horizontalSpeed -= step;
			}

			if (toDown)
			{
				verticalSpeed += step;
			}
			if (toUp)
			{
				verticalSpeed -= step;
			}
		}


		void Draw()
		{
			if (x1 < 0)
			{
				horizontalSpeed = -horizontalSpeed;
			}
			if (x2 > maxRight)
			{
				horizontalSpeed = -horizontalSpeed;
			}
			if (y1 < 0)
			{
				verticalSpeed = -verticalSpeed;
			}
			if (y2 > maxDown)
			{
				verticalSpeed = -verticalSpeed;
			}


			this->x1 += horizontalSpeed;
			this->x2 += horizontalSpeed;

			this->y1 += verticalSpeed;
			this->y2 += verticalSpeed;

			if (verticalSpeed > 0)
			{
				verticalSpeed -= braking;
			}
			if (verticalSpeed < 0)
			{
				verticalSpeed += braking;
			}

			if (horizontalSpeed > 0)
			{
				horizontalSpeed -= braking;
			}
			if (horizontalSpeed < 0)
			{
				horizontalSpeed += braking;
			}
		}
		
		void Stop()
		{
			toDown = toUp = toRight = toLeft = false;
		}
};

Ellipce *ellipce = new Ellipce(0, 0, 100, 100);

bool isMoveEllipce = false;
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

    // TODO: Place code here.
	

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB1MAINPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1MAINPROJECT));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1MAINPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1MAINPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   RECT clientRect;
   int windowWidth = windowHeight = 0;

   if (GetClientRect(hWnd, &clientRect))
   {
	   windowWidth = clientRect.right - clientRect.left;
	   windowHeight = clientRect.bottom - clientRect.top;
   }
   ellipce->maxRight = windowWidth;
   ellipce->maxDown = windowHeight;
   //windowWidth = clientRect->right - clientRect->left;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   SetTimer(hWnd, DRAW_TIMER, TIMER_INTERVAL, (TIMERPROC)NULL);
   SetTimer(hWnd, SPEED_TIMER, TIMER_INTERVAL, (TIMERPROC)NULL);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
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
		HDC hDC, hCompatibleDC;
		PAINTSTRUCT PaintStruct;
		HANDLE hBitmap, hOldBitmap;
		RECT Rect;
		BITMAP Bitmap;

            hDC = BeginPaint(hWnd, &PaintStruct);
//			Ellipse(hdc, ellipce->x1, ellipce->y1, ellipce->x2, ellipce->y2);
			hBitmap = LoadImage(NULL, L"csharp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

			GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
			hCompatibleDC = CreateCompatibleDC(hDC);
			hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
			StretchBlt(hDC, ellipce->x1, ellipce->y1, ellipce->x2 - ellipce->x1, ellipce->y2 - ellipce->y1, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
			SelectObject(hCompatibleDC, hOldBitmap);
			DeleteObject(hBitmap);
			DeleteDC(hCompatibleDC);
			EndPaint(hWnd, &PaintStruct);
        }
        break;
	case WM_SIZE:
		{
		RECT clientRect;
		int windowWidth = windowHeight = 0;

		if (GetClientRect(hWnd, &clientRect))
		{
			windowWidth = clientRect.right - clientRect.left;
			windowHeight = clientRect.bottom - clientRect.top;
		}
		ellipce->maxRight = windowWidth;
		ellipce->maxDown = windowHeight;
		}
		break;
	case WM_LBUTTONDOWN:
		{

		}
		break;
	case WM_LBUTTONUP:
		{

		}
		break;
	case WM_KEYDOWN:
		
		switch (wParam)
		{
		case VK_RIGHT:
			{
			ellipce->toRight = true;
			}
			break;
		case VK_LEFT:
			{
			ellipce->toLeft = true;
			}
			break;
		case VK_DOWN:
			{
			ellipce->toDown = true;
			}
			break;
		case VK_UP:
			{
			ellipce->toUp = true;
			}
			break;
		}
		break;
	case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_RIGHT:
				{
				ellipce->toRight = false;
				}
				break;
			case VK_LEFT:
				{
				ellipce->toLeft = false;
				}
				break;
			case VK_DOWN:
				{
				ellipce->toDown = false;
				}
				break;
			case VK_UP:
				{
				ellipce->toUp = false;
				}
				break;
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			int fwKeys = GET_KEYSTATE_WPARAM(wParam);
			if (fwKeys == MK_SHIFT)
			{
				if (zDelta > 0)
				{
					ellipce->horizontalSpeed -= ellipce->step * 2;
				}
				if (zDelta < 0)
				{
					ellipce->horizontalSpeed += ellipce->step * 2;
				}
			}
			else
			{
				if (zDelta > 0)
				{
					ellipce->verticalSpeed -= ellipce->step * 2;
				}
				if (zDelta < 0)
				{
					ellipce->verticalSpeed += ellipce->step * 2;
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
			ellipce->Draw();
			
			InvalidateRect(hWnd, NULL, TRUE);
			//UpdateWindow(hWnd);
		}
		break;
		case SPEED_TIMER:
		{
			ellipce->ProcessKeys();
		}
		break;
		}
	}
		break;
    case WM_DESTROY:
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
