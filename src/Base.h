#pragma once

#include "Singleton.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

//Return the current window
#define _GetWindow C_Base::getInstance()->GetWindow()

//Return the current renderer
#define _GetRenderer C_Base::getInstance()->GetRenderer()

class C_Base{


public:

    //INLINE
    
    static C_Base* getInstance();

    SDL_Window* GetWindow();

    SDL_Renderer* GetRenderer();

private:
    
    C_Base();
    
    ~C_Base();
    
    SDL_Window* mainWindow;

    SDL_Renderer* mainRenderer;

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




