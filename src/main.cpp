#include "Game.h"

using namespace std;

//Variables to store the screen dimensions
int SCREEN_WIDTH;
int SCREEN_HEIGHT;

//Variables to store the scale in comparison to 720p
float SCALE_W;
float SCALE_H;

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
        SCREEN_WIDTH = dM.h;
        SCREEN_HEIGHT = dM.w;
    }
    
    else if (dM.w > dM.h)
    {
        SCREEN_WIDTH = dM.w;
        SCREEN_HEIGHT = dM.h;
    }
    
    else
    {
        SCREEN_WIDTH = dM.w;
        SCREEN_HEIGHT = dM.h;
    }
    
    //Log the SCREEN WIDTH and SCREEN HEIGHT
    m1::Log("SCREEN WIDTH: "+ m1::to_string(SCREEN_WIDTH));
    m1::Log("SCREEN HEIGHT: "+ m1::to_string(SCREEN_HEIGHT));
    
    //DEFINE THE SCALE
    SCALE_W = (float)SCREEN_WIDTH/1280;
    SCALE_H = (float)SCREEN_HEIGHT/720;
    
    //LOG THE SCALE
    m1::Log( "SCALE_W = " + m1::to_string(SCALE_W) );
    m1::Log( "SCALE_H = " + m1::to_string(SCALE_H) );
    
    //CREATE THE STATIC GAMEOBJECT TEXTURES
    C_GameObject::CreateStaticObjects();
    
	//Is used to check if the main game loop is valid
    bool quitPollEvent = false;

    //Event to check the current event
    SDL_Event e;
    
    //The main Game
    C_Game mainGame;
        
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
                    quitPollEvent = true;
                }
            }
        }
        
        //Clear screen with the default render color
        SDL_RenderClear(_GetRenderer);

		//Call the main game play function
        mainGame.Game_Play();
        
        //Sync the renderer
        SDL_RenderPresent(_GetRenderer);

        ++fps;
        
		//Print the FPS every second
        if(SDL_GetTicks() - lt >= 1000)
		{
            lt = SDL_GetTicks();
            m1::Log( "FPS: " + m1::to_string(fps) );
            fps = 0;
        }
    
    }

    //CLEAR THE MEMORY
    C_GameObject::DeleteStaticObjects();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}


