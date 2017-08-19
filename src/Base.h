#pragma once

#include "Singleton.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern float SCALE_W;
extern float SCALE_H;

//Return the current window
#define _GetWindow C_Base::getInstance()->GetWindow()

//Return the current renderer
#define _GetRenderer C_Base::getInstance()->GetRenderer()

#define _GetBase C_Base::getInstance()

class C_Base{


public:

    //INLINE
    
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




