#include "Button.h"

void Button::init(const char* button_text, TTF_Font& font)
{
	this->init_texture_from_text(button_text, &font);
	texture_rect_double.w = texture_rect.w;
	texture_rect_double.h = texture_rect.h;

}

