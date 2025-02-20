#include <windows.h>
#include <cstdio>
#include <cstdlib>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char szClassName[] = "CodeBlocksWindowsApp";
HWND hEdit1, hEdit2;
HWND hBtnAdd, hBtnSub, hBtnMul, hBtnDiv;
HWND hLabel;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    static HBRUSH hbrBkgnd = CreateSolidBrush(RGB(255, 0, 128));

    wincl.hInstance     = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc   = WindowProcedure;
    wincl.style         = CS_DBLCLKS;
    wincl.cbSize        = sizeof(WNDCLASSEX);
    wincl.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName  = NULL;
    wincl.cbClsExtra    = 0;
    wincl.cbWndExtra    = 0;
    wincl.hbrBackground = hbrBkgnd;

    if(!RegisterClassEx(&wincl))
        return 0;

    hwnd = CreateWindowEx(
        0,
        szClassName,
        "My Calculator",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        250,
        200,
        HWND_DESKTOP,
        NULL,
        hThisInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);
    while(GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return (int)messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CREATE:
            hLabel = CreateWindow("STATIC", "Please input two numbers",
                                  WS_VISIBLE | WS_CHILD,
                                  25, 10, 200, 20, hwnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                                  85, 40, 80, 25, hwnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                                  85, 70, 80, 25, hwnd, NULL, NULL, NULL);
            hBtnAdd = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                   50, 110, 30, 30, hwnd, (HMENU)1, NULL, NULL);
            hBtnSub = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                   90, 110, 30, 30, hwnd, (HMENU)2, NULL, NULL);
            hBtnMul = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                   130, 110, 30, 30, hwnd, (HMENU)3, NULL, NULL);
            hBtnDiv = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                   170, 110, 30, 30, hwnd, (HMENU)4, NULL, NULL);
            break;
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case 1:
                case 2:
                case 3:
                case 4:
                {
                    char buff1[50], buff2[50];
                    GetWindowText(hEdit1, buff1, 50);
                    GetWindowText(hEdit2, buff2, 50);
                    double num1 = atof(buff1);
                    double num2 = atof(buff2);
                    double result = 0.0;
                    bool validOperation = true;
                    switch(LOWORD(wParam))
                    {
                        case 1: result = num1 + num2; break;
                        case 2: result = num1 - num2; break;
                        case 3: result = num1 * num2; break;
                        case 4:
                            if(num2 != 0.0)
                                result = num1 / num2;
                            else
                            {
                                MessageBox(hwnd, "Cannot divide by zero", "Result", MB_OK | MB_ICONERROR);
                                validOperation = false;
                            }
                            break;
                    }
                    if(validOperation)
                    {
                        char resultStr[50];
                        sprintf(resultStr, "%.9g", result);
                        MessageBox(hwnd, resultStr, "Result", MB_OK);
                    }
                }
                break;
            }
        }
        break;
        case WM_SYSCOMMAND:
            if((wParam & 0xFFF0) == SC_MAXIMIZE) return 0;
            if((wParam & 0xFFF0) == SC_SIZE) return 0;
            return DefWindowProc(hwnd, message, wParam, lParam);
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
