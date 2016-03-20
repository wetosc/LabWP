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
HBITMAP btfly;
int x,y;
float angle, angle2;
/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wid = 256, hei = 256;
    switch (message)                  /* handle the messages */
    {
    case WM_DESTROY:
    {
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    }
    case WM_CREATE:
    {
        x=250;
        y=250;
        angle = 0;
        SetTimer(hwnd, 0,100,NULL);
        btfly = (HBITMAP) LoadImage(NULL, "butterfly.bmp", IMAGE_BITMAP,wid,hei, LR_LOADFROMFILE);
    }
    case WM_PAINT:
    {

        PAINTSTRUCT ps;
        RECT rc;
        GetClientRect(hwnd, &rc);
        HDC hdc = BeginPaint (hwnd, &ps) ;
        HDC bitmapDC = CreateCompatibleDC(hdc);

        FillRect(hdc, &rc, CreateSolidBrush(RGB(255,255,255)));

        SelectObject(bitmapDC,btfly);
        BitBlt(hdc, x,y,wid,hei, bitmapDC, 0,0, SRCCOPY);
        MoveToEx(hdc, 500, 500, NULL);
        LineTo(hdc, x+wid/2+27, y+hei-55);
        int t1=x+wid/2 + 200*cos(angle),t2=y+hei/2 + 200*sin(angle);
        SelectObject(hdc, CreateSolidBrush(RGB(0,255,0)));
        Ellipse (hdc,t1-10,t2-10,t1+10,t2+10 );
        t1=x+wid/2 + 200*cos(angle2); t2=y+hei/2 + 200*sin(angle2);
        TextOut(hdc,t1,t2, "Cernei Eugeniu", strlen("Cernei Eugeniu"));

        DeleteDC(bitmapDC);
        EndPaint (hwnd, &ps) ;
    }
    case WM_TIMER:
    {
        int a = rand()%11-5, b = rand()%10-5;
        angle -= 3.14*5/180;
        angle2 += 3.14*0.5/180;
        if (x+a<500) x+=a;
        else x-=a;
        if (y+b<500) y+=b;
        else y-=b;
        if (x+a<0) x+=4*abs(a);
        if (y+b<0) y+=4*abs(b);
        InvalidateRect(hwnd, NULL, FALSE);

    }

    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
