#ifndef USERINTERFACE_H
#define USERINTERFACE_H


class UserInterface
{

private:

	//forward declaration of functions

	HINSTANCE hInstance;
	WNDPROC wndProc;
	HWND mainWindow;
	HWND glWin;

public:
	UserInterface(void);
	~UserInterface(void);

	void CreateMainWindow(const char *, const char * , HINSTANCE);
	void RegisterMainWindow(WNDPROC, char const *, HINSTANCE);
	void SetVisible(int);


	void CreateGLWindow(const char *, WNDPROC, HINSTANCE);
	void CreateButton(const char *, int, int, int, int);

	HWND GetGLWindow();


};
#endif
