#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE hInst;
HBRUSH hRed, hGreen, hBlue, hDefaultColor, current_color;
HWND handles[8];
int x=160, y=18;
int dx=2,dy=1;
float alfa = 0, pi = 3.14;
int current_fig=0;
HWND hwnd;
RECT upd_rect;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreviousInstance, PSTR szCmdLine,int iCmdShow) {
	MSG message;
	WNDCLASS windowClass;
	
	memset(&windowClass,0,sizeof(windowClass));
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(hInst,"icon");
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = CreateSolidBrush(RGB(240, 240, 245));
	windowClass.lpszClassName = "Class name";
	
	if (!RegisterClass(&windowClass)) {
		MessageBox(hwnd, "Class registration failed", "Error", MB_OK);
		return 0;
	}
	
	hwnd=CreateWindow("Class name", "Window name", WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	if (!hwnd) {
		MessageBox(hwnd, "Window registration failed", "Error", MB_OK);
		return 0;
	}
	
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	
	while(GetMessage(&message,NULL,0,0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.lParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	enum 
	{ 	
		H_RADIO_1, 
		RADIO_1, 
		RADIO_2, 
		RADIO_3, 
		H_CHECK_1, 
		H_CHECK_2, 
		H_CHECK_3, 
		CHECK_1, 
		CHECK_2, 
		CHECK_3, 
		H_BUTTON_1, 
		BUTTON_1, 
		BUTTON_2, 
		CIRCLE, 
		SQUARE, 
		ELLIPSE 
	};
	
	switch(message) 
	{
		case WM_CREATE: 
		{
			handles[H_CHECK_1] = CreateWindow("button", "Red", WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, 10, 10, 100, 20, hWnd, (HMENU)CHECK_1, hInst, NULL);
			handles[H_CHECK_2] = CreateWindow("button", "Green", WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, 10, 30, 100, 20, hWnd, (HMENU)CHECK_2, hInst, NULL);
			handles[H_CHECK_3] = CreateWindow("button", "Blue", WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, 10, 50, 100, 20, hWnd, (HMENU)CHECK_3, hInst, NULL);
			
			handles[H_RADIO_1] = CreateWindow("button", "Circle", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, 150, 10, 100, 20, hWnd, (HMENU)RADIO_1, hInst, NULL);
			handles[H_RADIO_1] = CreateWindow("button", "Square", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, 150, 30, 100, 20, hWnd, (HMENU)RADIO_2, hInst, NULL);
			handles[H_RADIO_1] = CreateWindow("button", "Ellipse", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, 150, 50, 100, 20, hWnd, (HMENU)RADIO_3, hInst, NULL);
			
			handles[H_BUTTON_1] = CreateWindow("button", "Start", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 10, 80, 60, 20, hWnd, (HMENU)BUTTON_1, hInst, NULL);
			handles[H_BUTTON_1] = CreateWindow("button", "Stop", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 100, 80, 60, 20, hWnd, (HMENU)BUTTON_2, hInst, NULL);
		
			upd_rect.bottom = 350;
			upd_rect.left = 45;
			upd_rect.right = 400;
			upd_rect.top = 0;
			hRed = CreateSolidBrush(RGB(250, 0, 0));
			hGreen= CreateSolidBrush(RGB(0, 250, 0));
			hBlue = CreateSolidBrush(RGB(0, 0, 250));
			hDefaultColor = CreateSolidBrush(RGB(255,255,255));
			current_fig = CIRCLE;
			break;
		}
		case WM_PAINT: 
		{
		    HDC hdc;
		    PAINTSTRUCT ps;
		    hdc = BeginPaint(hWnd, &ps);
		    SelectObject(hdc, current_color);
			RECT rect;
			GetClientRect(hWnd, &rect);
		    
		    double diagonal = sqrt(rect.right * rect.right + rect.bottom * rect.bottom) / 25;
		    
			switch(current_fig) 
			{
				case CIRCLE:
					Ellipse(hdc, x-diagonal, y-diagonal, x+diagonal, y+diagonal);
					break;
				
				case ELLIPSE:
					Ellipse(hdc, x-diagonal, y-diagonal*2, x+diagonal, y+diagonal*2);
					break;
		
				case SQUARE:
					Rectangle(hdc, x-diagonal, y-diagonal, x+diagonal, y+diagonal);
					break;
			}
			int ends = 10;
			upd_rect.left = x-diagonal-ends;
			upd_rect.top = y-diagonal*2-ends;
			upd_rect.right = x+diagonal+ends;
			upd_rect.bottom = y+diagonal*2+ends;
				
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_TIMER:
		{
			RECT rect;
			GetClientRect(hWnd, &rect);
			
			//rect.right -= 200;
			//rect.bottom -= 200;
			
			x = (rect.right / 4) * cos(alfa * pi / 30 - pi / 2) + rect.right / 4 + 200;
			y = (rect.bottom / 4) * sin(alfa * pi / 30 - pi / 2) + rect.bottom / 4 + 200;
			
			alfa += 0.1;
			InvalidateRect(hWnd, &upd_rect, TRUE);
			break;
		}
 
		case WM_COMMAND: 
		{
			switch(LOWORD(wParam)) 
			{
				case RADIO_1:
					current_fig = CIRCLE;
					InvalidateRect(hWnd, &upd_rect, TRUE);
					break;
					
				case RADIO_2:
					current_fig = SQUARE;
					InvalidateRect(hWnd, &upd_rect, TRUE);
					break;
	
				case RADIO_3:
					current_fig = ELLIPSE;
					InvalidateRect(hWnd, &upd_rect, TRUE);
					break;
	
				case CHECK_1:
				{
					bool flag = true;
					if(SendMessage(handles[H_CHECK_1], BM_GETCHECK, 0, 0) == BST_CHECKED)
					flag = false;
					EnableWindow( handles[H_CHECK_2], flag);
					EnableWindow( handles[H_CHECK_3], flag);
					flag ? current_color = hDefaultColor : current_color = hRed;
					InvalidateRect(hWnd, &upd_rect, TRUE);
					break;
				}
				case CHECK_2:
				{
					bool flag = true;
					if( SendMessage(handles[H_CHECK_2], BM_GETCHECK, 0,
					0)==BST_CHECKED )
					flag = false;
					EnableWindow( handles[H_CHECK_1], flag);
					EnableWindow( handles[H_CHECK_3], flag);
					flag ? current_color = hDefaultColor : current_color = hGreen;
					InvalidateRect(hWnd, &upd_rect, TRUE);
					break;
				}
				case CHECK_3:
				{
					bool flag = true;
					if( SendMessage(handles[H_CHECK_3], BM_GETCHECK, 0,
					0)==BST_CHECKED )
					flag = false;
					EnableWindow( handles[H_CHECK_1], flag);
					EnableWindow( handles[H_CHECK_2], flag);
					flag ? current_color = hDefaultColor : current_color = hBlue;
					InvalidateRect(hWnd, &upd_rect, TRUE);
					break;
				}
				case BUTTON_1:
				{
					SetTimer(hWnd, 0, 1, NULL);
					break;
				}
				case BUTTON_2:
				{
					KillTimer(hWnd, 0);
					break;
				}
			}
			break;
		}
		case WM_DESTROY:
	    	PostQuitMessage(0);
	    	break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
