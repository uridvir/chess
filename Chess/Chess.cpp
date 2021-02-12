// Chess.cpp : Defines the entry point for the application.
//
#include "framework.h"
#include "Chess.h"

#include <windowsx.h>

#include "Game.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
HWND mainWindow;								// Main window
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Chess::Game game;								// Chess game state
Chess::Position originPos;						// Square where drag started

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void				pieceToText(Chess::PieceType piece, TCHAR* textBuffer);

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
      CW_USEDEFAULT, 0, 415, 455, nullptr, nullptr, hInstance, nullptr);

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

			auto state = game.getBoardState();
            
			for (int column = 0; column < 8; column++)
			{
				for (int row = 0; row < 8; row++)
				{
					//Draw border around cell
					RECT rect;
					rect.left = column * 50;
					rect.top = row * 50;
					rect.right = (column + 1) * 50;
					rect.bottom = (row + 1) * 50;
					DrawEdge(hdc, &rect, EDGE_RAISED, BF_RECT);

					//Print piece description in cell
					TCHAR textBuffer[3];
					pieceToText(state[7 - row][column], textBuffer);
					TextOut(hdc, column * 50 + 15, row * 50 + 15, textBuffer, 2);
				}
			}

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
		{
			//Debugging
			//OutputDebugStringA("Button down!\n");
			
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			int file = xPos / 50 + 1;
			int rank = 8 - (yPos / 50);

			auto pos = Chess::Position(file, rank);

			if (pos.exists())
			{
				//Debugging
				/*
				char debug[100];
				sprintf_s(debug, 100, "Origin file %d and rank %d\n", file, rank);
				OutputDebugStringA(debug);
				*/

				originPos = pos;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			//Debugging
			//OutputDebugStringA("Button up!\n");

			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			int file = xPos / 50 + 1;
			int rank = 8 - (yPos / 50);

			auto pos = Chess::Position(file, rank);
			
			if (pos.exists())
			{
				//Debugging
				/*
				char debug[100];
				sprintf_s(debug, 100, "Destination file %d and rank %d\n", file, rank);
				OutputDebugStringA(debug);
				*/

				auto destinationPos = pos;
				game.makeMove(originPos, destinationPos);
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
			}
			originPos = Chess::Position();
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

	switch (piece.species)
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