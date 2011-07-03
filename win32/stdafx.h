#pragma once



typedef double SCALAR;

//Forward declaration of classes
class GameController;

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <gl\gl.h>		
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <SDL.h>
#include "SDL_opengl.h" 





// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

// TODO: reference additional headers your program requires here
#include "Resource.h"

#include "Volume.h"
#include "UserInterface.h"
#include "GLContext.h"
#include "Vector.h"
#include "Object.h"
#include "Crate.h"
#include "Ship.h"
#include "Player.h"
#include "Enemy.h"
#include "GameController.h"


#include "wglext.h"

#define PI 3.14159265

#define SKY_TEX 1
#define CRATE_TEX 2

#define DRAG(V, C) (0.5*V*V*C)

extern GameController gameController;


