#pragma once
#include "Global.h"

class C_Base{


public:

    //INLINE
	//Variables to store the screen dimensions
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static Uint32 WINDOWFLAGS;

	//Variables to store the scale in comparison to 720p
	static float SCALE_W;
	static float SCALE_H;

    static C_Base* getInstance();

    SDL_Window* GetWindow();

    SDL_Renderer* GetRenderer();

	void SyncSettings();

	void SetFullscreen(bool state);

	void SetResolution(int w, int h);

	bool IsFullscreen()
	{
		return isFullscreen;
	}

private:
    
    C_Base();
    
    ~C_Base();
    
    SDL_Window* mainWindow;

    SDL_Renderer* mainRenderer;

	bool isFullscreen;

	bool changedFullscreenState;

	int resW;
	int resH;

};

inline C_Base* C_Base::getInstance()
{
    static C_Base instance;
    return &instance;
}



inline SDL_Window* C_Base::GetWindow(){

    return mainWindow;

};

inline SDL_Renderer* C_Base::GetRenderer(){

    return mainRenderer;

};




