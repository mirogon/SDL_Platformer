#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <experimental/filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <M1Serialization/M1Serialization.h>


#ifdef __ANDROID__

#include <android/log.h>

#endif

#include <iostream>

#define _PATH_MENU_FONT "../data/ttf/opensans.ttf"
#define _PATH_FONT "../data/ttf/opensans.ttf"
#define _PATH_PLAYER "../data/png/Player.png"
#define _PATH_DIRT "../data/png/Dirt.png"
#define _PATH_BACKGROUND "../data/png/Background.png"

#define _SCREEN_WIDTH Base::screen_width
#define _SCREEN_HEIGHT Base::screen_height
#define _WINDOWFLAGS Base::windowflags
#define _SCALE_W Base::scale_w
#define _SCALE_H Base::scale_h

//Return the current window
#define _get_window Base::get_instance()->get_window()

//Return the current renderer
#define _get_renderer Base::get_instance()->get_renderer()

//Return the static Base instance
#define _get_base Base::get_instance()

//Player
const float MAX_VELOCITY = 20.0f;
const float VELOCITY_CHANGE_FALL = 0.075;
const float PLAYER_WALKSPEED = 7.5f;

using namespace m1;
using namespace std::experimental;

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

		double_Rect(double x_, double y_, int w_, int h_): x{x_}, y{y_}, w{w_}, h{h_}
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
	enum E_BlockType { NONE = -1, DIRT = 0 };

	enum E_GameState { state_Quit = -1, state_Menu = 0, state_menu_settings = 1, state_Play = 2, state_Editor_Edit = 3, state_Editor_Load = 4 };

	struct S_GameState
	{
		short current_state; //-1 = Quit, 0 = Menu, 1 = Play, 2 = Editor, 3 = menu_settings

		S_GameState(short c_state) : current_state{ c_state }
		{

		}

		void changeState(short new_state)
		{
			current_state = new_state;
		}
	};

	//Enum to check the collision direction
	enum E_CollisionDirection { Left = 0, Right = 1, Bot = 2, Top = 3 };

	inline E_CollisionDirection collision_detection(const double_Rect& p_collision_box, const double_Rect& collision_box)
	{
		float w = 0.5 * (p_collision_box.w + collision_box.w);
		float h = 0.5 * (p_collision_box.h + collision_box.h);
		float dx = double_Rect::GetCenterX(p_collision_box) - double_Rect::GetCenterX(collision_box);
		float dy = double_Rect::GetCenterY(p_collision_box) - double_Rect::GetCenterY(collision_box);

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
	bool key_is_pressed(SDL_Scancode scancode);

	inline bool key_is_pressed(SDL_Scancode scancode)
	{
		static const Uint8* key_status = SDL_GetKeyboardState(NULL);
		key_status = SDL_GetKeyboardState(NULL);

		if (key_status[scancode] == 1)
		{
			return true;
		}

		else
		{
			return false;
		}

	}

	//CHECK IF A COORDINATE IS IN A RECT
	bool is_in_collision_box(int x, int y, const SDL_Rect& collision_box);
	bool is_in_collision_box(int x, int y, const double_Rect& collision_box);

	inline bool is_in_collision_box(int x, int y, const SDL_Rect& collision_box)
	{
		if (x < (collision_box.x + collision_box.w) && (x > collision_box.x))
		{
			if (y < (collision_box.y + collision_box.h) && (y > collision_box.y))
			{
				return true;
			}
		}
		return false;
	}

	inline bool is_in_collision_box(int x, int y, const double_Rect& collision_box)
	{
		if (x < (collision_box.x + collision_box.w) && (x > collision_box.x))
		{
			if (y < (collision_box.y + collision_box.h) && (y > collision_box.y))
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

	//MULTIPLATFORM log
	void log(std::string str, int delay = 0);

#ifdef __ANDROID__

	inline void log(std::string str, int delay)
	{
		if (delay>0)
		{
			SDL_Delay(delay);
		}

		__android_log_print(ANDROID_log_FATAL, "TRACKER_M1", "%s", str.c_str());
	}

#endif

#ifdef __LINUX__

	inline void log(std::string str, int delay)
	{

		if (delay>0)
		{
			SDL_Delay(delay);
		}

		std::cout << str << std::endl;

	}

#endif

#ifdef __WINDOWS__

	inline void log(std::string str, int delay)
	{
		if (delay>0)
		{
			SDL_Delay(delay);
		}

		std::cout << str << std::endl;
	}

#endif

	//WRITE CHAR STRING IN FILE
	inline void SDL_WriteChar(SDL_RWops* rops, const char* c)
	{
		SDL_RWwrite(rops, c, 1, SDL_strlen(c));
	}

	template<typename T>
	void safe_delete(T* t)
	{
		if (t != nullptr)
		{
			delete t;
			t = nullptr;
		}
	}


}
