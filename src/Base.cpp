#include "Base.h"

Base::Base() :

	//Intializing the main_window
	main_window{ SDL_CreateWindow("SDL_Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE) },

	//Intializing the main_renderer
	main_renderer{ SDL_CreateRenderer(main_window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) },

	is_fullscreen{ true },

	changed_fullscreen_state{false},

	res_w{_SCREEN_WIDTH},

	res_h{_SCREEN_HEIGHT}

{
    if(!main_window)
	{
        //std::cout<<"main_window could not be intialized"<<std::endl;
        m1::log("Window could not be created!");
    }

    if(!main_renderer)
	{
        //std::cout<<"main_renderer could not be intialized"<<std::endl;
        m1::log("main_renderer could not be created!");
    }

    //Set the default renderer color
    SDL_SetRenderDrawColor(main_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

};

Base::~Base(){

    //Destroy the main_window
    SDL_DestroyWindow(this->main_window);
	main_window = nullptr;

    //Destroy the main_renderer
    SDL_DestroyRenderer(this->main_renderer);
	main_renderer = nullptr;
};

void Base::set_fullscreen(bool state)
{
	is_fullscreen = state;
	changed_fullscreen_state = true;
}

void Base::set_resolution(int w, int h)
{
	res_w = w;
	res_h = h;
}

void Base::sync_settings()
{
	if (res_w != screen_width || res_h != screen_height)
	{
		screen_width = res_w;
		screen_height = res_h;
		scale_w = (float)screen_width / 1280;
		scale_h = (float)screen_height / 720;

		m1::log("NEW Screen Details");
		m1::log("screen_width: " + m1::to_string(screen_width));
		m1::log("screen_height: " + m1::to_string(screen_height));
		m1::log("_SCALE_W: " + m1::to_string(_SCALE_W));
		m1::log("scale_h: " + m1::to_string(scale_h));

		SDL_SetWindowSize(_get_window, res_w, res_h);
		
	}

	if (changed_fullscreen_state)
	{

		if (is_fullscreen == true)
		{
			if (SDL_SetWindowFullscreen(main_window, SDL_WINDOW_FULLSCREEN) != 0)
			{
				std::cout << SDL_GetError() << std::endl;
			}
		}

		else
		{
			if (SDL_SetWindowFullscreen(main_window, 0) != 0)
			{
				std::cout << SDL_GetError() << std::endl;
			}
		}

		changed_fullscreen_state = false;

	}

}

//Variables to store the screen dimensions
int Base::screen_width = 0;
int Base::screen_height = 0;
Uint32 Base::windowflags = 0;

//Variables to store the scale in comparison to 720p
float Base::scale_w = 0;
float Base::scale_h = 0;
