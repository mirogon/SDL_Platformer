#include "Button.h"

void C_Button::Init(char* buttonText, TTF_Font& font)
{
	this->InitTextureFromText(buttonText, &font);
	textureRectDouble.w = textureRect.w;
	textureRectDouble.h = textureRect.h;

}

