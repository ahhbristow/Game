#pragma once


//Forward declaration of classes
class GameController;


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



#define PI 3.14159265

#define SKY_TEX 1
#define CRATE_TEX 2

#define DRAG(V, C) (0.5*V*V*C)

extern GameController gameController;


