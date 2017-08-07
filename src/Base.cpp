#include "Base.h"

C_Base::C_Base() :

	//Intializing the mainWindow
	mainWindow{ SDL_CreateWindow("SDL_Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN) },

	//Intializing the mainRenderer
	mainRenderer{ SDL_CreateRenderer(mainWindow, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) },

	isFullscreen{ true },

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

    //Destroy the mainRenderer
    SDL_DestroyRenderer(this->mainRenderer);

};

void C_Base::SetFullscreen(bool state)
{

	isFullscreen = state;



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

		SDL_DestroyWindow(mainWindow);
		SDL_DestroyRenderer(mainRenderer);

		if (isFullscreen == true)
		{
			mainWindow = SDL_CreateWindow("SDL_Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resW, resH, SDL_WINDOW_FULLSCREEN);
		}
		
		else
		{
			mainWindow = SDL_CreateWindow("SDL_Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resW, resH, 0);
		}

		mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	else {

		if (isFullscreen == true)
		{
			SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN);
		}

		else
		{
			SDL_SetWindowFullscreen(mainWindow, 0);
		}
	}

}