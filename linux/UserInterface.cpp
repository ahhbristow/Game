#include "UserInterface.h"

UserInterface::UserInterface(void)
{
}


UserInterface::~UserInterface(void)
{

}

void UserInterface::RegisterMainWindow(WNDPROC wndProc, char const * className, HINSTANCE hInst) {
	
	WNDCLASS wcex;

	wcex.style         = 0;			// Windows Style (future article)
	wcex.lpfnWndProc   = wndProc;			// The Window Procedure
	wcex.cbClsExtra    = 0;			// Extra memory for this class
	wcex.cbWndExtra    = 0;			// Extra memory for this window
	wcex.hInstance     = hInst;			// The definition of the instance of the application
	wcex.hIcon         = 0;			// The icon in the upper left corner
	wcex.hCursor       = ::LoadCursor(0, IDC_ARROW);	// The cursor for this window
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// The background color for this window
	wcex.lpszMenuName  = 0;			// The name of the class for the menu for this window
	wcex.lpszClassName = className;		// The name of this class

	::RegisterClass(&wcex);
}

void UserInterface::CreateMainWindow(char const * caption, char const * className, HINSTANCE hInstance) {
	mainWindow = ::CreateWindow(
		className,		// Name of the registered window class
		caption,		// Window Caption to appear at the top of the frame
		WS_OVERLAPPEDWINDOW,	// The style of window to produce (overlapped is standard window for desktop)
		0,	// x position of the window
		0,	// y position of the window
		1000,	// width of the window
		800,	// height of the window
		0,		// The handle to the parent frame (we will use this later to simulate an owned window)
		0,		// The handle to the menu for this window (we will learn to create menus in a later article)
		hInstance, 	// the application instance
		0);		// window creation data
}



void UserInterface::CreateButton(const char *caption, int left, int top, int width, int height) {
	::CreateWindow(
		"BUTTON",		// Name of the registered window class
		caption,		// Window Caption to appear at the top of the frame
		WS_VISIBLE,	// The style of window to produce (overlapped is standard window for desktop)
		left,	// x position of the window
		top,	// y position of the window
		width,	// width of the window
		height,	// height of the window
		mainWindow,		// The handle to the parent frame (we will use this later to simulate an owned window)
		(HMENU)BUTTON,		// The handle to the menu for this window (we will learn to create menus in a later article)
		hInstance, 	// the application instance
		0
	);		// window creation data
}

void UserInterface::SetVisible(int cmdShow) {	
	// Makes the window visible after it is created
	::ShowWindow(mainWindow, cmdShow);
	::UpdateWindow(mainWindow);
}


void UserInterface::CreateGLWindow(const char *caption, WNDPROC wndProc, HINSTANCE hInst) {
	//Create a container for the openGl window
	WNDCLASSEX wcex;
	const char *classname = "GLWINDOW";

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= classname;
	wcex.hIconSm		= NULL;
	RegisterClassEx(&wcex);

	int glWidth = 984;
	int glHeight = 762;
	this->glWin = CreateWindow(classname, caption, WS_VISIBLE | WS_CHILD,
      0, 0, glWidth, glHeight, this->mainWindow, NULL, hInst, NULL);
}

HWND UserInterface::GetGLWindow() {

	return this->glWin;
}


