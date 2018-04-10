//============================================================================
// Name        : Set_Pixel.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Screen.h"

using namespace cave;

int main(int argc, char *argv[])
    {
    Screen screen;

    //initalize everything, if something is wrong cout error
    if (screen.init() == false)
	{
	cout << "Error initialising SDL!" << endl;
	}

    //game loop	-update particles, draw particles, check for messages/events
    while (true)
	{
	//set a big block of color
	for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) //work your way down screen
	    {
	    for (int x = 0; x < Screen::SCREEN_WIDTH; x++) //work your way across screen
		{
		screen.setPixel(x, y, 0, 245, 255, 255);
		}
	    }

	//set one pixel a color
	screen.setPixel(330, 440, 0, 0, 0, 255);

	//draw onto screen
	screen.update();

	if (screen.processEvents() == false)
	    {
	    break; //break out of loop!
	    }
	}
    screen.close();
    return 0;
    }
