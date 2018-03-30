/*
 * Screen.cpp
 *
 *  Created on: Mar 29, 2018
 *      Author: jpetterson
 */

#include "Screen.h"

namespace cave
    {
    
    Screen::Screen() : //initionalze instance var in initionalation list form
	    m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL)
	{

	}

    bool Screen::init()
	{
	//check if SDL initialized correctly, will return neg number if no
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	    {
	    return false;
	    }
	//create a window
	m_window = SDL_CreateWindow("Particle Fire Explosion",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//if window doesn't load, run the quit function
	if (m_window == NULL)
	    {
	    SDL_Quit();
	    return false;
	    }

	//create the renderer
	m_renderer = SDL_CreateRenderer(m_window, -1,
		SDL_RENDERER_PRESENTVSYNC);

	//create texture
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	//check if renderer was created successfully
	if (m_renderer == NULL) //NULL is returned if something went wrong per API (google)
	    {
	    SDL_DestroyWindow(m_window); //if we could create window but not renderer
	    SDL_Quit();
	    return false;
	    }

	//check if texture was created successfully
	if (m_texture == NULL) //NULL is returned if something went wrong
	    {
	    SDL_DestroyWindow(m_window); //if we could create window but not renderer
	    SDL_DestroyRenderer(m_renderer); //if we could create the renderer but not the texture
	    SDL_Quit();
	    return false;
	    }

	//create the buffer area
	m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //Uint32 is SDL's version of 'int'

	//memset=set a block of memory with a perticular value
	memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	return true;
	}
    void Screen::update()
	{
	SDL_UpdateTexture(m_texture, NULL, m_buffer,
		SCREEN_WIDTH * sizeof(Uint32)); //update the texture with info being held in the buffer
	SDL_RenderClear(m_renderer); //clear out the renderer
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); //copy new info into renderer
	SDL_RenderPresent(m_renderer); //draw on the screen
	}

    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue,
	    Uint8 alpha)
	{

	Uint32 color = 0; // Uint32 is a 4 byte int   ie  00000000

	color += red; //add red value  (2 digit value b/c of the Uint8)
	color <<= 8; //shift red left 2 places
	color += green; //add green value to the right
	color <<= 8; //shift left 2 places
	color += blue; //add blue value to the right
	color <<= 8; //shift left 2 places
	color += alpha; //add alpha value to right

	m_buffer[(y * SCREEN_WIDTH) + x] = color; //put color into this pixel in the buffer

	}

    bool Screen::processEvents()
	{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	    {
	    if (event.type == SDL_QUIT)
		{
		return false;
		}
	    }
	return true;
	}

    void Screen::close()
	{
	delete[] m_buffer; // b/c we used 'new' we must free or delete this info
	SDL_DestroyTexture(m_texture); //destroy resources used for the texture
	SDL_DestroyRenderer(m_renderer); //destroy resources used for the renderer
	SDL_DestroyWindow(m_window); //kills the anything to do with the window

	SDL_Quit(); //quit SDL stuff
	}
    }

/* namespace cave */
