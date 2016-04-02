#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <math.h>
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

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
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

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

bool isPlaying;
float angle;
int color, figure;
HWND checks[3];

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
    {
        HWND radioButton_1 = CreateWindowEx(0, "Button", "Rectangle", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 4, 10, 100, 20, hwnd, (HMENU)1, NULL, NULL);
        HWND radioButton_2 = CreateWindowEx(0, "Button", "Ellipse", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 4, 30, 100, 20, hwnd, (HMENU)2, NULL, NULL);
        HWND radioButton_3 = CreateWindowEx(0, "Button", "Pie", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 4, 50, 100, 20, hwnd, (HMENU)3, NULL, NULL);
        HWND checkBox_1 = CreateWindowEx(0,"Button","Red",WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,4,70,100,20,hwnd,(HMENU)4,NULL,NULL);
        HWND checkBox_2 = CreateWindowEx(0,"Button","Green",WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,4,90,100,20,hwnd,(HMENU)5,NULL,NULL);
        HWND checkBox_3 = CreateWindowEx(0,"Button","Blue",WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,4,110,100,20,hwnd,(HMENU)6,NULL,NULL);
        HWND pushButton_1 = CreateWindow( "Button", "Play", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,4,130,50,20,hwnd,(HMENU)7,NULL,NULL);
        HWND pushButton_2 = CreateWindow( "Button", "Pause", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,54,130,50,20,hwnd,(HMENU)8,NULL,NULL);
        checks[0] = checkBox_1;
        checks[1] = checkBox_2;
        checks[2] = checkBox_3;
        break;
    }
    case WM_COMMAND:
    {
        switch (wParam)
        {
        case 1:
            figure = 0;
            break;
        case 2:
            figure = 1;
            break;
        case 3:
            figure = 2;
            break;
        case 4:
            color = 0;
            if (SendMessage(checks[0], BM_GETCHECK,0,0 ) == BST_CHECKED)
            {
                EnableWindow(checks[1], false);
                EnableWindow(checks[2], false);
            }
            else
            {
                EnableWindow(checks[1], true);
                EnableWindow(checks[2], true);
            }
            break;
        case 5:
            if (SendMessage(checks[1], BM_GETCHECK,0,0 ) == BST_CHECKED)
            {
                EnableWindow(checks[0], false);
                EnableWindow(checks[2], false);
            }
            else
            {
                EnableWindow(checks[0], true);
                EnableWindow(checks[2], true);
            }
            color = 1;
            break;
        case 6:
            if (SendMessage(checks[2], BM_GETCHECK,0,0 ) == BST_CHECKED)
            {
                EnableWindow(checks[0], false);
                EnableWindow(checks[1], false);
            }
            else
            {
                EnableWindow(checks[0], true);
                EnableWindow(checks[1], true);
            }
            color = 2;
            break;
        case 7:
            SetTimer(hwnd, 7, 100, NULL);
            break;
        case 8:
            KillTimer(hwnd, 7);
            break;
        default:
            break;
        }
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        RECT rc;
        GetClientRect(hwnd, &rc);
        HDC hdc = BeginPaint (hwnd, &ps) ;
        FillRect(hdc, &rc, CreateSolidBrush(RGB(255,255,255)));

        switch (color)
        {
        case 0:
            SelectObject(hdc, CreateSolidBrush(RGB(255,0,0)));
            break;
        case 1:
            SelectObject(hdc, CreateSolidBrush(RGB(0,255,0)));
            break;
        case 2:
            SelectObject(hdc, CreateSolidBrush(RGB(0,0,255)));
            break;
        }
        int x= 300 + cos(angle)*100;
        int y= 150 + sin(angle)*100;
        switch (figure)
        {
        case 0:
            Rectangle(hdc, x-10, y-10, x+10, y+10);
            break;
        case 1:
            Ellipse(hdc, x-15, y-10, x+15, y+10);
            break;
        case 2:
            Pie(hdc, x-10, y-10, x+10, y+10, x-5,y-10,x+10,y+5);
            break;
        }
        EndPaint (hwnd, &ps) ;
        break;
    }

    case WM_TIMER:
    {
        angle+=3.14*5/180;
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
