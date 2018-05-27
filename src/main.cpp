#include "Game.h"

#undef main

int main(int argc, char* argv[]){
    
    //init SDL, IMG and TTF
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    //Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    
	//Create a SDL_Displaymode which has information about the current screen
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    
	//Check if the device is vertical or horizontal
    if(dm.h > dm.w)
    {
        _SCREEN_WIDTH = dm.h;
        _SCREEN_HEIGHT = dm.w;
    }
    
    else if (dm.w > dm.h)
    {
        _SCREEN_WIDTH = dm.w;
        _SCREEN_HEIGHT = dm.h;
    }
    
    else
    {
        _SCREEN_WIDTH = dm.w;
        _SCREEN_HEIGHT = dm.h;
    }


    //log the SCREEN WIDTH and SCREEN HEIGHT
    m1::log("SCREEN WIDTH: "+ m1::to_string(_SCREEN_WIDTH));
    m1::log("SCREEN HEIGHT: "+ m1::to_string(_SCREEN_HEIGHT));
    
    //DEFINE THE SCALE
    _SCALE_W = (float)_SCREEN_WIDTH/1280;
    _SCALE_H = (float)_SCREEN_HEIGHT/720;
    
    //log THE SCALE
    m1::log( "_SCALE_W = " + m1::to_string(_SCALE_W) );
    m1::log( "_SCALE_H = " + m1::to_string(_SCALE_H) );
    
  
	//Is used to check if the main game loop is valid
    bool quit_pollevent = false;

    //
	bool left_mousebutton_pressed = false;
    bool h_key_released = false;

    //Event to check the current event
    SDL_Event e;
    
    //The main Game
    Game main_game;
        
	//Stores the current game state
	S_GameState game_state = state_Menu;

    while(quit_pollevent == false)
	{
        static int fps = 0;
        static Uint32 lt = 0;
        
        //Sync the current event
        while( SDL_PollEvent(&e)!= 0 )
		{
            //Check if the application was closed
            if(e.type == SDL_QUIT){

                //End the application loop
                quit_pollevent = true;
                
            }

            //reset pressed/released states
            left_mousebutton_pressed = false;
            h_key_released = false;
            
            //CHECK FOR KEYBOARD INPUT
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
					game_state = state_Menu;
                }
            }
            if(e.type==SDL_KEYUP)
            {
                if(e.key.keysym.sym == SDLK_h )
                {
                    h_key_released = true;
                }
            }
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					left_mousebutton_pressed = true;
				}
				
			}
			

        }
        
        //Clear screen with the default render color
        SDL_RenderClear(_get_renderer);

		if (game_state.current_state == state_Menu)
		{
			game_state.current_state = main_game.menu(left_mousebutton_pressed);
		}

		else if (game_state.current_state == state_menu_settings)
		{
			if (main_game.menu_settings(left_mousebutton_pressed) == true)
			{
				game_state.changeState(state_Menu);
			}
		}

		//Call the main game play function
		else if(game_state.current_state == state_Play)
		{
			main_game.play();
		}
        
		else if (game_state.current_state == state_Quit)
		{
			quit_pollevent = true;
		}

		else if (game_state.current_state == state_Editor_Load)
		{
			if (main_game.editor_load(left_mousebutton_pressed) == true)
			{
				game_state.changeState(state_Editor_Edit);
			}
		}
        
		else if (game_state.current_state == state_Editor_Edit)
		{
			main_game.editor_edit(left_mousebutton_pressed);
		}

		else
		{
			game_state.changeState(state_Menu);
		}

        //Sync the renderer
        SDL_RenderPresent(_get_renderer);

        ++fps;
        
		//Print the FPS every second
        if(SDL_GetTicks() - lt >= 1000)
		{
            lt = SDL_GetTicks();
            //m1::log( "FPS: " + m1::to_string(fps) );
            fps = 0;
        }
    
    }

    //CLEAR THE MEMORY
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}


