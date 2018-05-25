#pragma once
#include "Object.h"
class Button : public Object
{

public:

	Button() = default;
	~Button() = default;

	void init(const char* button_text, TTF_Font& font);

	void render();

	void mouse_on_button();
	bool button_pressed(bool mouse_pressed);

};

inline void Button::render()
{
	this->render_object();
}

inline void Button::mouse_on_button()
{
	static int mouse_pos_x = 0, mouse_pos_y = 0;

	SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);

	if (is_in_collision_box(mouse_pos_x, mouse_pos_y, texture_rect_double) == true)
	{
		SDL_SetTextureAlphaMod(texture, 128);
	}

	else 
	{
		SDL_SetTextureAlphaMod(texture, 255);
	}
}

inline bool Button::button_pressed(bool mouse_pressed)
{
	static int mouse_pos_x = 0, mouse_pos_y = 0;

	SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);

	if (is_in_collision_box(mouse_pos_x, mouse_pos_y, texture_rect_double) == true)
	{
		if (mouse_pressed == true)
		{
			return true;
		}
	}

	return false;

}