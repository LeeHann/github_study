﻿// calculator.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "calculator.h"
#include <iostream>

using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CALCULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CALCULATOR));

    MSG msg;

    // 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALCULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CALCULATOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //유니코드 문자를 정수와 실수로 변환하기
   static TCHAR szTemp[256];

   const TCHAR* _str_pi = L"3.14";
   const TCHAR* _str_int = L"314";

   swprintf_s(szTemp, sizeof(szTemp) / sizeof(TCHAR), L"pi : %f , num : %d",
       _wtof(_str_pi),
       _wtoi(_str_int)
   );
   OutputDebugString(szTemp);


   //계산기
   CreateWindow(L"static", //클래스 종류
       L"계산기", //출력 텍스트
       WS_CHILD | WS_VISIBLE | WS_BORDER, //스타일
       100, 200, 150, 25, //위치(x,y), 크기(w,h)
       hWnd, //부모 윈도우
       (HMENU)2001, hInst, NULL);

   CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | WS_BORDER,
       100, 250, 250, 25,
       hWnd, (HMENU)3001, hInst, NULL);

   CreateWindow(L"button", L"+", WS_CHILD | WS_VISIBLE | BS_PUSHBOX,
       100, 300, 50, 25,
       hWnd, (HMENU)4001, hInst, NULL);
   CreateWindow(L"button", L"-", WS_CHILD | WS_VISIBLE | BS_PUSHBOX,
       150, 300, 50, 25,
       hWnd, (HMENU)5001, hInst, NULL);
   CreateWindow(L"button", L"*", WS_CHILD | WS_VISIBLE | BS_PUSHBOX,
       200, 300, 50, 25,
       hWnd, (HMENU)6001, hInst, NULL);
   CreateWindow(L"button", L"/", WS_CHILD | WS_VISIBLE | BS_PUSHBOX,
       250, 300, 50, 25,
       hWnd, (HMENU)7001, hInst, NULL);
   CreateWindow(L"button", L"=", WS_CHILD | WS_VISIBLE | BS_PUSHBOX,
       300, 300, 50, 25,
       hWnd, (HMENU)8001, hInst, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR szBuf[256];
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case 4001:
            {
                static TCHAR szTemp[256];
                GetWindowText(GetDlgItem(hWnd, 3001), szTemp, sizeof(szTemp) / sizeof(TCHAR));
                OutputDebugString(szTemp);

                if (szTemp[0]) {
                    swprintf_s(szBuf, sizeof(szBuf) / sizeof(TCHAR), L" % s % s + ", szBuf, szTemp);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
            break;
            case 5001:
            {
                static TCHAR szTemp[256];
                GetWindowText(GetDlgItem(hWnd, 3001), szTemp, sizeof(szTemp) / sizeof(TCHAR));
                OutputDebugString(szTemp);

                if (szTemp[0]) {
                    swprintf_s(szBuf, sizeof(szBuf) / sizeof(TCHAR), L" % s % s - ", szBuf, szTemp);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
            break;
            case 6001:
            {
                static TCHAR szTemp[256];
                GetWindowText(GetDlgItem(hWnd, 3001), szTemp, sizeof(szTemp) / sizeof(TCHAR));
                OutputDebugString(szTemp);

                if (szTemp[0]) {
                    swprintf_s(szBuf, sizeof(szBuf) / sizeof(TCHAR), L" % s % s * ", szBuf, szTemp);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
            break;
            case 7001:
            {
                static TCHAR szTemp[256];
                GetWindowText(GetDlgItem(hWnd, 3001), szTemp, sizeof(szTemp) / sizeof(TCHAR));
                OutputDebugString(szTemp);

                if (szTemp[0]) {
                    swprintf_s(szBuf, sizeof(szBuf) / sizeof(TCHAR), L" % s % s / ", szBuf, szTemp);
                    InvalidateRect(hWnd, NULL, TRUE);
                }
            }
            break;
            case 8001:
            {
                static TCHAR szTemp[256];
                GetWindowText(GetDlgItem(hWnd, 3001), szTemp, sizeof(szTemp) / sizeof(TCHAR));
                OutputDebugString(szTemp);
                //wcstok
                if (szTemp[0]) {
                    int ans1 = (int)szBuf[6] - 48, ans2;
                    for (int i = 0; i < sizeof(szBuf); i++)
                    {
                        ans2 = (int)szBuf[i+3] - 48;
                        if (szBuf[i] == '+')
                        {
                            ans1 = ans1 + ans2;
                        }
                        else if (szBuf[i] == '-')
                        {
                            ans1 = ans1 - ans2;
                        }
                        else if (szBuf[i] == '*')
                        {
                            ans1 = ans1 * ans2;
                        }
                        else if (szBuf[i] == '/')
                        {
                            ans1 = ans1 / ans2;
                        }
                    }
                    swprintf_s(szBuf, sizeof(szBuf) / sizeof(TCHAR), L" % s % s = %d", szBuf, szTemp, ans1);
                    InvalidateRect(hWnd, NULL, TRUE);
                }

            }
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
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            TextOut(hdc, 300, 50, szBuf, wcslen(szBuf));
            szBuf[0] = '\0';

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

// 정보 대화 상자의 메시지 처리기입니다.
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
