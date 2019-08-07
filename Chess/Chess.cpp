// Chess.cpp : Defines the entry point for the application.
//
#include "framework.h"
#include "Chess.h"

#include "Game.h"

#include <commctrl.h>
#pragma comment( lib, "comctl32.lib" )

#define MAX_LOADSTRING 100

#define GRID_ID 42

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND mainWindow;								// Main window
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Chess::Game game;								// Chess game state

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL				InitializeGrid(HWND hwndListView);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHESS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	INITCOMMONCONTROLSEX icxx;
	icxx.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icxx);
	HWND hwndGrid = CreateWindow(WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_NOCOLUMNHEADER | LVS_SINGLESEL | LVS_ALIGNTOP,
		10, 10, 400, 135, mainWindow, (HMENU) GRID_ID, hInst, 0);

	ListView_SetExtendedListViewStyle(hwndGrid, LVS_EX_GRIDLINES);

	InitializeGrid(hwndGrid);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHESS));

    MSG msg;

    // Main message loop:
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

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHESS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHESS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   mainWindow = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
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

// Message handler for about box.
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

//Converts PieceType to text representation
void pieceToText(Chess::PieceType piece, TCHAR* textBuffer)
{
	switch (piece.color)
	{
	case Chess::Color::White:
		textBuffer[0] = 'W';
		break;
	case Chess::Color::Black:
		textBuffer[0] = 'B';
		break;
	}

	switch (piece.type)
	{
	case Chess::PieceType::King:
		textBuffer[1] = 'K';
		break;
	case Chess::PieceType::Queen:
		textBuffer[1] = 'Q';
		break;
	case Chess::PieceType::Rook:
		textBuffer[1] = 'R';
		break;
	case Chess::PieceType::Knight:
		textBuffer[1] = 'N';
		break;
	case Chess::PieceType::Bishop:
		textBuffer[1] = 'B';
		break;
	case Chess::PieceType::Pawn:
		textBuffer[1] = 'P';
		break;
	case Chess::PieceType::None:
		textBuffer[0] = ' ';
		textBuffer[1] = ' ';
		break;
	}

	textBuffer[2] = 0;
}

//Initializes the grid with 8 columns and 8 rows
BOOL InitializeGrid(HWND hwndListView)
{
	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM;

	for (int iCol = 0; iCol < 8; iCol++) 
	{
		lvc.fmt = LVCFMT_LEFT;
		lvc.iSubItem = iCol;
		lvc.cx = 50;

		if (ListView_InsertColumn(hwndListView, iCol, &lvc) == -1)
		{
			return FALSE;
		}

	}

	game = Chess::Game();
	auto state = game.getBoardState();

	LVITEM item;
	item.mask = LVIF_TEXT;
	item.cchTextMax = 2;
	TCHAR textBuffer[3];

	int column;
	int row;

	auto fail = [column, row]() -> BOOL {
		char debug[100];
		sprintf_s(debug, 100, "Could not insert item at column %d, row %d\n", column, row);
		OutputDebugStringA(debug);
		return FALSE;
	};

	for (row = 0; row < 8; row++)
	{
		for (column = 0; column < 8; column++)
		{
			item.iItem = row;
			item.iSubItem = column;

			pieceToText(state[7 - row][column], textBuffer);
			item.pszText = textBuffer;

			if (column == 0)
			{
				if (ListView_InsertItem(hwndListView, &item) == -1)
				{
					return fail();
				}
			}
			else if (ListView_SetItem(hwndListView, &item) == -1)
			{
				return fail();
			}
		}
	}

	return TRUE;
}