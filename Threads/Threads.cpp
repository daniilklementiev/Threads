    // Threads.cpp : Defines the entry point for the application.

#include "framework.h"
#include "Threads.h"

#define MAX_LOADSTRING 100

#define CMD_BUTTON_1   1001
#define CMD_BUTTON_2   1002
#define CMD_BUTTON_3   1003
#define CMD_BUTTON_4   1004

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND list;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int threadCounter = 0;
void                StartThread();
void                StartThread2();
void                StartThread3();
void                StartThread4();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_THREADS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THREADS));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THREADS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(106, 90, 205));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_THREADS);
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
    case WM_CREATE:
        CreateWindowW(L"Button", L"Thread", WS_CHILD | WS_VISIBLE, 10, 10, 75, 23, hWnd,
                            (HMENU)CMD_BUTTON_1, hInst, 0);
        CreateWindowW(L"Button", L"Thread2", WS_CHILD | WS_VISIBLE, 10, 40, 75, 23, hWnd,
            (HMENU)CMD_BUTTON_2, hInst, 0);


        CreateWindowW(L"Button", L"Thread3", WS_CHILD | WS_VISIBLE, 10, 70, 75, 23, hWnd,
            (HMENU)CMD_BUTTON_3, hInst, 0);

        list = CreateWindowW(L"Listbox", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL, 100, 10, 270, 300, hWnd,
            NULL, hInst, 0);

        CreateWindowW(L"Button", L"Thread4", WS_CHILD | WS_VISIBLE, 10, 100, 75, 23, hWnd,
            (HMENU)CMD_BUTTON_4, hInst, 0);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case CMD_BUTTON_1:
                StartThread();
                break;
            case CMD_BUTTON_2:
                StartThread2();
                break;
            case CMD_BUTTON_3:
                StartThread3();
                break;
            case CMD_BUTTON_4:
                StartThread4();
                break;
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


DWORD WINAPI ThreadProc(LPVOID params) {
    WCHAR str[100] = L"\0";
    ++threadCounter;
    _itow_s(threadCounter, str, 10);
    MessageBoxW(NULL, (WCHAR*)str, (WCHAR*)params, MB_YESNOCANCEL);
    threadCounter = _wtoi(str);
    return 0;
}

void StartThread() {    // Button click handler
    CreateThread(
        NULL,           // Attribute for thread
        0,              // Stack limit (0 - sys default)
        ThreadProc,     // Address of thread fucntion
        szTitle,           // Pointer to parameter(s)
        0,              // Creation flags
        NULL            // Thread Id pointer
    );
}


DWORD WINAPI ThreadProc2(LPVOID params) {
    WCHAR str[100] = L"\0";
    ++threadCounter;
    _itow_s(threadCounter, str, 10);
    MessageBoxW(NULL, (WCHAR*)str, (WCHAR*)params, MB_YESNOCANCEL);
    threadCounter = _wtoi(str);
    return 0;
}

void StartThread2() {   
    CreateThread(
        NULL,           
        0,              
        ThreadProc2,    
        szTitle,            // Params to thread       
        0,              
        NULL            
    );

}
/********************************************************/

HANDLE hts[12]; // threads handles

float deposit = 100;
short activeThreads;    // threads counter
struct DepData {
    int month;
    float percent;
    DepData(int m, float p) : month{ m }, percent{ p } {}

};

DWORD WINAPI Finalizer(LPVOID params) {
    for (size_t i = 0; i < 12; i++)
    {
        if (hts[i] != NULL)
        {
            CloseHandle(hts[i]);
            hts[i] = NULL;
        }
    }
    WCHAR txt[100];
    _snwprintf_s(txt, 100, L"------ total %.2f", deposit);
    SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)txt);
    return 0;
}



DWORD WINAPI ThreadProc3(LPVOID params) {
    DepData* data = (DepData*)params;
    WCHAR txt[100];
    deposit *= 1 + data->percent / 100.0;
    _snwprintf_s(txt, 100, L"month %d perc %.2f, total %.2f", data->month, data->percent, deposit);
    SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)txt);
    delete data;
    activeThreads--;
    if (activeThreads == 0) // It was the last thread
    {
        // launch finalizer
        CreateThread(NULL, 0, Finalizer, NULL, 0, NULL);

    }
    return 0;
}



void StartThread3() {
 
    activeThreads = 0;

    for (size_t i = 0; i < 12; i++) {
        hts[i] = CreateThread(
            NULL,
            0,
            ThreadProc3,
            new DepData(1+i, 10),            // Params to thread       
            0,
            NULL
        );
        if (hts[i] != NULL) activeThreads++;
    } 
    
    // SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)L"End-for");
    
}


/************************************/
HANDLE hts4[12];              // threads handles
HANDLE mutex4 = NULL;               //  
int activeThreads4;         // threads counter


DWORD WINAPI Finalizer4(LPVOID params) {
    for (size_t i = 0; i < 12; i++)
    {
        if (hts4[i] != NULL)
        {
            CloseHandle(hts4[i]);
            hts4[i] = NULL;
        }
    }
    CloseHandle(mutex4);
    mutex4 = NULL;
    WCHAR txt[100];
    _snwprintf_s(txt, 100, L"------ total %.2f", deposit);
    SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)txt);
    return 0;
}

DWORD WINAPI ThreadProc4(LPVOID params) {
    DepData* data = (DepData*)params;
    WCHAR txt[100];
    DWORD waitResult = WaitForSingleObject(mutex4, INFINITE);
    if(waitResult == WAIT_OBJECT_0) {
        deposit *= 1 + data->percent / 100.0;
        _snwprintf_s(txt, 100, L"month %d perc %.2f, total %.2f", data->month, data->percent, deposit);
        // SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)txt);
        activeThreads4--;
        if (activeThreads4 == 0) // It was the last thread
    {
        // launch finalizer
        CreateThread(NULL, 0, Finalizer4, NULL, 0, NULL);
    }
        ReleaseMutex(mutex4);
    }
    else
    {
        SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)L"Mutex Wait Error");
    }
    delete data;
    return 0;
}


void StartThread4() {
    deposit = 100;
    activeThreads4 = 0;
    SendMessageW(list, LB_RESETCONTENT, 0, 0);
    if (mutex4 != NULL)
    {
        SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)L"????, ??? ????????");
        return;
    }
    
    mutex4 = CreateMutex(NULL, FALSE, NULL);
    if (mutex4 == NULL) {
        SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)L"Mutex Error");
        return;
    }
    else SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)L"Mutex OK");
    for (size_t i = 0; i < 12; i++) {
        hts4[i] = CreateThread(
            NULL,
            0,
            ThreadProc4,
            new DepData(1 + i, 10),            // Params to thread       
            0,
            NULL
        );
        if (hts4[i] != NULL) activeThreads4++;
    }
    SendMessageW(list, LB_ADDSTRING, 100, (LPARAM)L"End for");
}