#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
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
bool isInRadius(int cX, int cY, int x, int y, int error)
{
    return (abs(cX-x)<error && abs(cY-y)<error);
}

HBITMAP btfly;
int x,y, fmX,fmY;
POINT p1,p2;
float angle, angle2;
bool shouldMove, changeP1,changeP2;

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
        x=50;
        y=50;
        angle = 0;
        p1.x = 20; p1.y=50;
        p2.x = 300; p2.y = 200;
        btfly = (HBITMAP) LoadImage(NULL, "butterfly.bmp", IMAGE_BITMAP,wid,hei, LR_LOADFROMFILE);
        shouldMove = false;
        break;
    }
    case WM_PAINT:
    {

        PAINTSTRUCT ps;
        RECT rc;
        GetClientRect(hwnd, &rc);
        HDC hdc = BeginPaint (hwnd, &ps) ;
        HDC bitmapDC = CreateCompatibleDC(hdc);
        HDC rotDC = CreateCompatibleDC(bitmapDC);

        FillRect(hdc, &rc, CreateSolidBrush(RGB(255,255,255)));

        POINT arp[4];
        arp[0].x = p1.x;
        arp[0].y = p1.y;
        arp[1].x = 260;
        arp[1].y = 270;
        arp[2].x = 80;
        arp[2].y = 40;
        arp[3].x = p2.x;
        arp[3].y = p2.y;
        PolyBezier(hdc, arp,4);

        SelectObject(bitmapDC,btfly);

        POINT arr[3];
        arr[0].x=100;
        arr[0].y=100;
        arr[0].x=200;
        arr[0].y=80;
        arr[0].x=120;
        arr[0].y=200;

        SetGraphicsMode(hdc,GM_ADVANCED);
        XFORM xform;
        xform.eM11=cos(angle);
        xform.eM12=sin(angle);
        xform.eM21=-sin(angle);
        xform.eM22=cos(angle);
        xform.eDx=(float)x - cos(angle)*wid/2 + sin(angle)*hei/2;
        xform.eDy=(float)y - cos(angle)*hei/2 - sin(angle)*wid/2;

        SetWorldTransform(hdc,&xform);

        BitBlt(hdc, 0,0,wid,hei, bitmapDC, 0,0, SRCCOPY);

        DeleteDC(bitmapDC);
        DeleteDC(rotDC);
        EndPaint (hwnd, &ps) ;
        break;
    }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            x-=10;
            break;

        case VK_RIGHT:
            x+=10;
            break;

        case VK_UP:
            y-=10;
            break;

        case VK_DOWN:
            y+=10;
            break;

        case VK_HOME:
            angle+=0.1;
            break;

        case VK_END:
            angle-=0.1;
            break;
        }
        InvalidateRect(hwnd,NULL,false);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        fmX = GET_X_LPARAM(lParam);
        fmY = GET_Y_LPARAM(lParam);
        shouldMove = isInRadius(x,y,fmX,fmY,wid/2);
        changeP1 = isInRadius(p1.x,p1.y,fmX,fmY,10);
        changeP2 = isInRadius(p2.x,p2.y,fmX,fmY,10);
        break;
    }
    case WM_MOUSEMOVE:
    {
        if (shouldMove)
        {
            x+= GET_X_LPARAM(lParam)-fmX;
            y+= GET_Y_LPARAM(lParam)-fmY;
            fmX = GET_X_LPARAM(lParam);
            fmY = GET_Y_LPARAM(lParam);
            InvalidateRect(hwnd,NULL,false);
        }

        if (changeP1){
            p1.x+= GET_X_LPARAM(lParam)-fmX;
            p1.y+= GET_Y_LPARAM(lParam)-fmY;
            fmX = GET_X_LPARAM(lParam);
            fmY = GET_Y_LPARAM(lParam);
            InvalidateRect(hwnd,NULL,false);
        }
        if (changeP2){
            p2.x+= GET_X_LPARAM(lParam)-fmX;
            p2.y+= GET_Y_LPARAM(lParam)-fmY;
            fmX = GET_X_LPARAM(lParam);
            fmY = GET_Y_LPARAM(lParam);
            InvalidateRect(hwnd,NULL,false);
        }

        break;
    }
    case WM_LBUTTONUP:
    {
        shouldMove = false;
        changeP1 = false;
        changeP2 = false;
        break;
    }
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
