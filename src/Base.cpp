#include "Base.h"

C_Base::C_Base() :

	//Intializing the mainWindow
	mainWindow{ SDL_CreateWindow("SDL_Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE) },

	//Intializing the mainRenderer
	mainRenderer{ SDL_CreateRenderer(mainWindow, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) },

	isFullscreen{ true },

	changedFullscreenState{false},

	resW{SCREEN_WIDTH},

	resH{SCREEN_HEIGHT}

{
    if(!mainWindow){

        //std::cout<<"mainWindow could not be intialized"<<std::endl;
        m1::Log("Window could not be created!");
    }

    if(!mainRenderer){

        //std::cout<<"mainRenderer could not be intialized"<<std::endl;
        m1::Log("mainRenderer could not be created!");
    }


    //Set the default renderer color
    SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

};

C_Base::~C_Base(){

    //Destroy the mainWindow
    SDL_DestroyWindow(this->mainWindow);
	mainWindow = nullptr;

    //Destroy the mainRenderer
    SDL_DestroyRenderer(this->mainRenderer);
	mainRenderer = nullptr;
};

void C_Base::SetFullscreen(bool state)
{
	isFullscreen = state;
	changedFullscreenState = true;
}

void C_Base::SetResolution(int w, int h)
{
	resW = w;
	resH = h;
}

void C_Base::SyncSettings()
{
	if (resW != SCREEN_WIDTH || resH != SCREEN_HEIGHT)
	{
		SCREEN_WIDTH = resW;
		SCREEN_HEIGHT = resH;
		SCALE_W = (float)SCREEN_WIDTH / 1280;
		SCALE_H = (float)SCREEN_HEIGHT / 720;

		m1::Log("NEW Screen Details");
		m1::Log("SCREEN_WIDTH: " + m1::to_string(SCREEN_WIDTH));
		m1::Log("SCREEN_HEIGHT: " + m1::to_string(SCREEN_HEIGHT));
		m1::Log("SCALE_W: " + m1::to_string(SCALE_W));
		m1::Log("SCALE_H: " + m1::to_string(SCALE_H));

		SDL_SetWindowSize(_GetWindow, resW, resH);
		
	}

	if (changedFullscreenState)
	{

		if (isFullscreen == true)
		{
			if (SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN) != 0)
			{
				std::cout << SDL_GetError() << std::endl;
			}
		}

		else
		{
			if (SDL_SetWindowFullscreen(mainWindow, 0) != 0)
			{
				std::cout << SDL_GetError() << std::endl;
			}
		}

		changedFullscreenState = false;

	}

}

