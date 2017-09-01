#include "Game.h"

#undef main

using namespace std;




int main(int argc, char* argv[]){
    
    //Init SDL, IMG and TTF
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    //Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    
	//Create a SDL_Displaymode which has information about the current screen
    SDL_DisplayMode dM;
    SDL_GetCurrentDisplayMode(0, &dM);
    
	//Check if the device is vertical or horizontal
    if(dM.h > dM.w)
    {
        _SCREEN_WIDTH = dM.h;
        _SCREEN_HEIGHT = dM.w;
    }
    
    else if (dM.w > dM.h)
    {
        _SCREEN_WIDTH = dM.w;
        _SCREEN_HEIGHT = dM.h;
    }
    
    else
    {
        _SCREEN_WIDTH = dM.w;
        _SCREEN_HEIGHT = dM.h;
    }


    //Log the SCREEN WIDTH and SCREEN HEIGHT
    m1::Log("SCREEN WIDTH: "+ m1::to_string(_SCREEN_WIDTH));
    m1::Log("SCREEN HEIGHT: "+ m1::to_string(_SCREEN_HEIGHT));
    
    //DEFINE THE SCALE
    _SCALE_W = (float)_SCREEN_WIDTH/1280;
    _SCALE_H = (float)_SCREEN_HEIGHT/720;
    
    //LOG THE SCALE
    m1::Log( "_SCALE_W = " + m1::to_string(_SCALE_W) );
    m1::Log( "_SCALE_H = " + m1::to_string(_SCALE_H) );
    
  
	//Is used to check if the main game loop is valid
    bool quitPollEvent = false;
	bool leftMousePressed = false;

    //Event to check the current event
    SDL_Event e;
    
    //The main Game
    C_Game mainGame;
        
	//Stores the current game state
	S_GameState gameState = state_Menu;

    while(quitPollEvent == false)
	{
        static int fps = 0;
        static Uint32 lt = 0;
        
        //Sync the current event
        while( SDL_PollEvent(&e)!= 0 )
		{
            //Check if the application was closed
            if(e.type == SDL_QUIT){

                //End the application loop
                quitPollEvent = true;
                
            }
            
            //CHECK FOR KEYBOARD INPUT
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
					gameState = state_Menu;
                }
            }

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					leftMousePressed = true;
				}
				else
				{
					leftMousePressed = false;
				}
				
			}

			else
			{
				leftMousePressed = false;
			}
			

        }
        
        //Clear screen with the default render color
        SDL_RenderClear(_GetRenderer);

		if (gameState.currentState == state_Menu)
		{
			gameState.currentState = mainGame.Game_Menu(leftMousePressed);
		}

		else if (gameState.currentState == state_Menu_Settings)
		{
			if (mainGame.Game_Menu_Settings(leftMousePressed) == true)
			{
				gameState.changeState(state_Menu);
			}
		}

		//Call the main game play function
		else if(gameState.currentState == state_Play)
		{
			mainGame.Game_Play();
		}
        
		else if (gameState.currentState == state_Quit)
		{
			quitPollEvent = true;
		}
        
		else
		{
			gameState.changeState(state_Menu);
		}

        //Sync the renderer
        SDL_RenderPresent(_GetRenderer);

        ++fps;
        
		//Print the FPS every second
        if(SDL_GetTicks() - lt >= 1000)
		{
            lt = SDL_GetTicks();
            //m1::Log( "FPS: " + m1::to_string(fps) );
            fps = 0;
        }
    
    }

    //CLEAR THE MEMORY
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}


