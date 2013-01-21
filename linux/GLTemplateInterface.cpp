#include "GLTemplateInterface.h"

//==== Forward function declaration =========
LRESULT CALLBACK WindowProcedure(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam);
void GetWorldCoordinate();


bool mouseDown = false;
bool key_down, key_left, key_right, key_up = false;


//==== Game Objects ==========================
Object *objects;
Player *player;
Crate *crate;
GameController gameController;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow) {
	

	CreateGUI(hInst, cmdShow);


	//========== Initialisation =====================
	

	InitGame();


	//================ Main Program Loop ================/

	MSG  msg;
	while(true) {

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Translate the message and dispatch it to WindowProc()
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		// If the message is WM_QUIT, exit the while loop
		if(msg.message == WM_QUIT)
			break;


		if(key_up) {
			glContext->zRot -= 1.0f;
		}

		if(key_down) {
			
			glContext->zRot += 1.0f;
		}

		if(key_right) {
		
			glContext->xRot += 2.0f;
		}

		if(key_left) {
		
			glContext->xRot -= 2.0f;
		}

		GameLoop();

	}
	
	return msg.wParam;
}


LRESULT CALLBACK WindowProcedure(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam) {

	int wmId, wmEvent;
	POINT *currentMouse = new POINT();
	

	::GetCursorPos(currentMouse);

	wmId    = LOWORD(wParam);
	wmEvent = HIWORD(wParam);

	switch(message) {
		case WM_COMMAND:


		case WM_LBUTTONDOWN:
			gameController.GetPlayer()->Fire(currentMouse->x, currentMouse->y);
			gameController.UpdateObjects(1);
			GetWorldCoordinate();
			mouseDown = true;
			return 0;

		case WM_LBUTTONUP:
			mouseDown = false;
			return 0;


		case WM_MOUSEMOVE:
			return 0;

		case WM_MOUSEHOVER:
			::ShowCursor(false);
			return 0;


		case WM_KEYDOWN:
			switch(wParam) {

			case VK_LEFT:
				key_left = true;
				break;

			case VK_UP:
				key_up = true;
				break;

			case VK_RIGHT:
				key_right = true;
				break;

			case VK_DOWN: 
				key_down = true;
				break;

			}

			return 0;

		case WM_KEYUP:
			switch(wParam) {

			case VK_LEFT:
				key_left = false;
				break;

			case VK_UP:
				key_up = false;
				break;

			case VK_RIGHT:
				key_right = false;
				break;

			case VK_DOWN: 
				key_down = false;
				break;

			}
			return 0;

		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
	

	}
	
	return ::DefWindowProc(hwnd, message, wParam, lParam);
}


//===========  Game setup, loop and tear down functions ==============

void InitGame() 
{
	//load textures
	glContext->loadTextures("dawn.bmp", 1);
	glContext->loadTextures("crate.bmp", 2);
	
	gameController.SetGLContext(glContext);


	//set initial game state (no objects fired, health etc)
	
}

void GameLoop() 
{
	//render objects
	gameController.UpdateObjects(0);

}

void CreateGUI(HINSTANCE hInst, int cmdShow) {
	const char className[] = "Program";

	//create user interface
	UserInterface userInterface;
	userInterface.RegisterMainWindow(WindowProcedure, className, hInst);
	userInterface.CreateMainWindow("Crate Game", className, hInst);
	userInterface.SetVisible(cmdShow);
	userInterface.CreateGLWindow("Crate Game", WindowProcedure, hInst);
	//userInterface.CreateButton("Rotate", 700, 0, 100, 50);
	
	glContext = new GLContext(userInterface.GetGLWindow());
}


void GetWorldCoordinate() {
	POINT currentMouse;
	::GetCursorPos(&currentMouse);

	int x = currentMouse.x;
	int y = currentMouse.y;

	GLdouble nearX, nearY, nearZ, farX, farY, farZ;


	GLdouble	*model;
	GLdouble	projection[16];
	GLint		viewport[4];
	GLfloat 	depth = 0;

		
	//get depth value
	glReadBuffer(GL_BACK);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
	glReadPixels(0, 0, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	model = gameController.glContext->GetModelviewMatrix();
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);


	gluUnProject(x, y, depth, model, projection, viewport, &nearX, &nearY, &nearZ);

	int z;

}
