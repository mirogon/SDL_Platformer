#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <M1Serialization.h>


#ifdef __ANDROID__

#include <android/log.h>

#endif

#include <iostream>
#include "randomNumber.h"

#define _MenuFontPath "../data/ttf/opensans.ttf"
#define _FontPath "../data/ttf/opensans.ttf"
#define _PlayerPath "../data/png/Player.png"
#define _DirtPath "../data/png/Dirt.png"
#define _BackgroundPath "../data/png/Background.png"


struct double_Rect {

	double x;
	double y;
	int w;
	int h;

	static int GetCenterX(const double_Rect& a)
	{
		return a.x + a.w / 2;
	}
	static int GetCenterY(const double_Rect& a)
	{
		return a.y + a.h / 2;
	}
};

//NAMESPACE FOR USEFUL FUNCTIONS
namespace m1{
    

    //CHECK IF THE KEY WITH THE SCANCODE scancode IS PRESSED
    bool KeyIsPressed(SDL_Scancode scancode);
    
    inline bool KeyIsPressed(SDL_Scancode scancode)
    {
        static const Uint8* keyStatus = SDL_GetKeyboardState(NULL);
        keyStatus = SDL_GetKeyboardState(NULL);
        
        if(keyStatus[scancode] == 1)
        {
            return true;
        }
        
        else
        {
            return false;
        }
        
    }
    
    //CHECK IF A COORDINATE IS IN A SDL_RECT

	

    bool IsInCollisionBox(int x, int y, const SDL_Rect& collisionBox);
	bool IsInCollisionBox(int x, int y, const double_Rect& collisionBox);

    inline bool IsInCollisionBox(int x, int y, const SDL_Rect& collisionBox)
	{
        if(x < ( collisionBox.x + collisionBox.w ) && ( x > collisionBox.x ) )
		{
            if( y < ( collisionBox.y + collisionBox.h ) && ( y > collisionBox.y ) )
			{
                return true;
            }
        }
        return false;
    }

	inline bool IsInCollisionBox(int x, int y, const double_Rect& collisionBox) 
	{
		if (x < (collisionBox.x + collisionBox.w) && (x > collisionBox.x)) 
		{
			if (y < (collisionBox.y + collisionBox.h) && (y > collisionBox.y)) 
			{
				return true;
			}
		}
		return false;
	}
    
    //CAST EVERYTHING TO A STRING
    template <typename T>
    std::string to_string(T value)
    {
        std::ostringstream os ;
        os << value ;
        return os.str() ;
    }
    
    //CAST A STRING TO A LONG VARIABLE
    long stol(std::string str);
    
    inline long stol(std::string str)
    {
        std::stringstream sstr(str);
        long rt;
        sstr >> rt;
        return rt;
    }
    
    //MULTIPLATFORM LOG
    void Log(std::string str, int delay = 0);
    
    #ifdef __ANDROID__
    
    inline void Log(std::string str, int delay)
	{
        if(delay>0)
		{
            SDL_Delay(delay);
        }

		__android_log_print(ANDROID_LOG_FATAL, "TRACKER_M1", "%s", str.c_str() );
    }
    
    #endif
    
    #ifdef __LINUX__
    
        inline void Log(std::string str, int delay)
		{
       
			if(delay>0)
			{
				 SDL_Delay(delay);
			 }
        
        std::cout<<str<<std::endl;
        
    }
    
    #endif

	#ifdef __WINDOWS__

		inline void Log(std::string str, int delay) 
		{
			if (delay>0) 
			{
				SDL_Delay(delay);
			}

			std::cout << str << std::endl;
		}

	#endif

    //WRITE CHAR STRING IN FILE
    void SDL_WriteChar(SDL_RWops* rops, const char* c);
    
    inline void SDL_WriteChar(SDL_RWops* rops, const char* c)
    {
        SDL_RWwrite(rops, c, 1, SDL_strlen(c));
    }
    
    template<typename T>
    void SafeDelete(T t);
    
    template<typename T>
    void SafeDelete(T* t)
	{
        if(t != nullptr)
		{
            delete t;
            t = nullptr;
        }
    }
    

}
