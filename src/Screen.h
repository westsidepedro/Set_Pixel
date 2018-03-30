/*
 * Screen.h
 *
 *  Created on: Mar 29, 2018
 *      Author: jpetterson
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>
#include <string.h>
#include <iostream>
using namespace std;

namespace cave
    {
    
    class Screen
	{
	public:
	    const static int SCREEN_WIDTH = 800; //static b/c we only need one value for all ref
	    const static int SCREEN_HEIGHT = 600; //not a different on for each call

	private:
	    SDL_Window *m_window; // m_  to let us know that it is a instance var not LOCAL var
	    SDL_Renderer *m_renderer;
	    SDL_Texture *m_texture;
	    Uint32 *m_buffer;

	public:
	    Screen(); //constructor
	    bool init(); // T/F  false if fails true if successeds
	    bool processEvents(); //event processing
	    void update(); // draw to screen
	    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue,
		    Uint8 alpha); // set pixel color
	    void close(); //close down code

	};
    
    } /* namespace cave */

#endif /* SCREEN_H_ */
