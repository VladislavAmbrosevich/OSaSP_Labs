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
		bool toRight = false, toLeft = false, toDown = false, toUp = false;

	Ellipce(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	public:
		void Draw()
		{
			if (this->toRight)
			{
				this->MoveRight();
			}
			if (this->toLeft)
			{
				this->MoveLeft();
			}
			if (this->toDown)
			{
				this->MoveDown();
			}
			if (this->toUp)
			{
				this->MoveUp();
			}
		}
		
		void Stop()
		{
			this->toDown = false;
			this->toUp = false;
			this->toRight = false;
			this->toLeft = false;
		}

	private: 
		void MoveLeft()
		{
			this->x1--;
			this->x2--;
		}

		void MoveRight()
		{
			this->x1++;
			this->x2++;
		}

		void MoveDown()
		{
			this->y1++;
			this->y2++;
		}

		void MoveUp()
		{
			this->y1--;
			this->y2--;
		}
};

Ellipce *ellipce = new Ellipce(0, 0, 100, 100);

bool isMoveEllipce = false;
UINT_PTR timer;
const int TIMER_KEY_RIGHT = 0, TIMER_KEY_LEFT = 1, TIMER_KEY_UP = 2, TIMER_KEY_DOWN = 3;
const int TIMER_WHEEL_UP = 4, TIMER_WHEEL_DOWN = 5;
const int DRAW_TIMER = INT_MAX;
const int TIMER_INTERVAL = 10;

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

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   SetTimer(hWnd, DRAW_TIMER, TIMER_INTERVAL, (TIMERPROC)NULL);

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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			Ellipse(hdc, ellipce->x1, ellipce->y1, ellipce->x2, ellipce->y2);
            EndPaint(hWnd, &ps);
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
					//ellipce->Stop();
				ellipce->toUp = false;
				}
				break;
			}
			//KillTimer(hWnd, DRAW_TIMER);
		}
		break;
	case WM_MOUSEWHEEL:
		{
			/*int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			if (zDelta > 0)
			{
				SetTimer(hWnd, TIMER_WHEEL_UP, TIMER_INTERVAL, (TIMERPROC)NULL);
			}
			if (zDelta < 0)
			{
				SetTimer(hWnd, TIMER_WHEEL_DOWN, TIMER_INTERVAL, (TIMERPROC)NULL);
			}
			if (zDelta = 0)
			{
				KillTimer(hWnd, TIMER_KEY_DOWN);
				KillTimer(hWnd, TIMER_WHEEL_UP);
			}*/
			//if (wParam)
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
			UpdateWindow(hWnd);
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
