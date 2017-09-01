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

#define _SCREEN_WIDTH C_Base::SCREEN_WIDTH
#define _SCREEN_HEIGHT C_Base::SCREEN_HEIGHT
#define _WINDOWFLAGS C_Base::WINDOWFLAGS
#define _SCALE_W C_Base::SCALE_W
#define _SCALE_H C_Base::SCALE_H

//Return the current window
#define _GetWindow C_Base::getInstance()->GetWindow()

//Return the current renderer
#define _GetRenderer C_Base::getInstance()->GetRenderer()

#define _GetBase C_Base::getInstance()

const float maxVelocity = 20.0f;
const float velocityChangeFall = 0.075;
const float playerWalkSpeed = 7.5f;

using namespace m1;

namespace m1 {

	struct double_Coordinate
	{
		double_Coordinate(): x(0), y(0)
		{}

		double_Coordinate(double x_, double y_): x{x_}, y{y_}
		{}

		double x;
		double y;
	};

	struct double_Rect {

		double x;
		double y;
		int w;
		int h;

		double_Rect(): x(0), y(0), w(0), h(0)
		{}

		static int GetCenterX(const double_Rect& a)
		{
			return a.x + a.w / 2;
		}
		static int GetCenterY(const double_Rect& a)
		{
			return a.y + a.h / 2;
		}
	};
	enum E_BlockType { Dirt = 0 };

	enum e_GameState { state_Quit = -1, state_Menu = 0, state_Play = 1, state_Editor = 2, state_Menu_Settings = 3 };

	struct S_GameState
	{
		short currentState; //-1 = Quit, 0 = Menu, 1 = Play, 2 = Editor, 3 = Menu_Settings

		S_GameState(short cState) : currentState{ cState }
		{

		}

		void changeState(short newState)
		{
			currentState = newState;
		}
	};

	//Enum to check the collision direction
	enum E_CollisionDirection { Left = 0, Right = 1, Bot = 2, Top = 3 };

	inline E_CollisionDirection CollisionDetection(const double_Rect& pCollisionBox, const double_Rect& collisionBox)
	{
		float w = 0.5 * (pCollisionBox.w + collisionBox.w);
		float h = 0.5 * (pCollisionBox.h + collisionBox.h);
		float dx = double_Rect::GetCenterX(pCollisionBox) - double_Rect::GetCenterX(collisionBox);
		float dy = double_Rect::GetCenterY(pCollisionBox) - double_Rect::GetCenterY(collisionBox);

		if (abs(dx) <= w && abs(dy) <= h)
		{
			/* collision! */
			float wy = w * dy;
			float hx = h * dx;

			if (wy > hx)
			{
				if (wy > -hx)
				{
					return Bot;
				}

				else
				{
					return Left;
				}
			}

			else
			{
				if (wy > -hx)
				{
					return Right;
				}

				else
				{
					return Top;
				}

			}

		}

	}
	//CHECK IF THE KEY WITH THE SCANCODE scancode IS PRESSED
	bool KeyIsPressed(SDL_Scancode scancode);

	inline bool KeyIsPressed(SDL_Scancode scancode)
	{
		static const Uint8* keyStatus = SDL_GetKeyboardState(NULL);
		keyStatus = SDL_GetKeyboardState(NULL);

		if (keyStatus[scancode] == 1)
		{
			return true;
		}

		else
		{
			return false;
		}

	}

	//CHECK IF A COORDINATE IS IN A RECT
	bool IsInCollisionBox(int x, int y, const SDL_Rect& collisionBox);
	bool IsInCollisionBox(int x, int y, const double_Rect& collisionBox);

	inline bool IsInCollisionBox(int x, int y, const SDL_Rect& collisionBox)
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
		std::ostringstream os;
		os << value;
		return os.str();
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
		if (delay>0)
		{
			SDL_Delay(delay);
		}

		__android_log_print(ANDROID_LOG_FATAL, "TRACKER_M1", "%s", str.c_str());
	}

#endif

#ifdef __LINUX__

	inline void Log(std::string str, int delay)
	{

		if (delay>0)
		{
			SDL_Delay(delay);
		}

		std::cout << str << std::endl;

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
	void SafeDelete(T* t)
	{
		if (t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}


}
