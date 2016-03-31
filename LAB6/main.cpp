#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               1000,                 /* The programs width */
               500,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    DWORD err =  GetLastError();
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

void drawNumbers(HDC hdc)
{
    int t1=50,t2=50;
    int cx = 200, cy = 200, r = 150;
    TCHAR texts[][12] = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    for (int i=0; i<12; i++)
    {
        t1 = cx + cos((i-2)*3.14/6)*r - 5;
        t2 = cy + sin((i-2)*3.14/6)*r - 5;
        TextOut(hdc,t1,t2, texts[i], strlen(texts[i]));
    }

}
float angle, angle2;
int sec, min;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_DESTROY:
    {
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    }
    case WM_CREATE:
    {
        SetTimer(hwnd, 1,1000,NULL);
        SetTimer(hwnd, 60,60000,NULL);
        angle = -3.14/2;
        angle2 = -3.14/2;
        break;
    }
    case WM_PAINT:
    {

        PAINTSTRUCT ps;
        RECT rc;
        GetClientRect(hwnd, &rc);
        HDC hdc = BeginPaint (hwnd, &ps) ;

        FillRect(hdc, &rc, CreateSolidBrush(RGB(255,255,255)));
        drawNumbers(hdc);

        MoveToEx(hdc, 200, 200, NULL);
        LineTo(hdc, 200+cos(angle)*130,200+sin(angle)*130);

        MoveToEx(hdc, 200, 200, NULL);
        LineTo(hdc, 200+cos(angle2)*100,200+sin(angle2)*100);

        char txt[3];
        int len = sprintf (txt,"%02d : %02d",min,sec);
        TextOut(hdc,500,100, txt, len);

        EndPaint (hwnd, &ps) ;
        break;
    }
    case WM_TIMER:
    {
        switch (wParam)
        {
        case 1:
        {
            angle+=3.14/30;
            sec++;
            if (sec>=60) sec=0;
            break;
        }
        case 60:
        {
            min++;
            if (min>=60) min=0;
            angle2+=3.14/30;
            break;
        }
        }
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    }
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }


    return 0;
}
