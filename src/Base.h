#pragma once
#include "Global.h"

class Base{


public:

    //INLINE
	//Variables to store the screen dimensions
	static int screen_width;
	static int screen_height;
	static Uint32 windowflags;

	//Variables to store the scale in comparison to 720p
	static float scale_w;
	static float scale_h;

    static Base* get_instance();

    SDL_Window* get_window();

    SDL_Renderer* get_renderer();

	void sync_settings();

	void set_fullscreen(bool state);

	void set_resolution(int w, int h);

	bool check_if_fullscreen()
	{
		return is_fullscreen;
	}

private:
    
    Base();
    
    ~Base();
    
    SDL_Window* main_window;

    SDL_Renderer* main_renderer;

	bool is_fullscreen;

	bool changed_fullscreen_state;

	int res_w;
	int res_h;

};

inline Base* Base::get_instance()
{
    static Base instance;
    return &instance;
}



inline SDL_Window* Base::get_window(){

    return main_window;

};

inline SDL_Renderer* Base::get_renderer(){

    return main_renderer;

};




