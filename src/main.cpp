#include <iostream>
#include"raylib.h"
#include"FE.h"
using namespace std;

const int screenW = 1512;
const int screenH = 982;

int main()
{
	InitWindow(screenW, screenH, "Crossing Road");  
	CreateMenu(screenW, screenH);
	return 0;
}