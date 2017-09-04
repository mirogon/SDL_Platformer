#pragma once
#include "Object.h"
class C_Button : public C_Object
{

public:

	void MouseOnButton();
	bool ButtonPressed(bool mousePressed);

};

inline void C_Button::MouseOnButton()
{
	static int mousePosX = 0, mousePosY = 0;

	SDL_GetMouseState(&mousePosX, &mousePosY);

	if (IsInCollisionBox(mousePosX, mousePosY, textureRectDouble) == true)
	{
		SDL_SetTextureAlphaMod(texture, 128);
	}

	else 
	{
		SDL_SetTextureAlphaMod(texture, 255);
	}
}

inline bool C_Button::ButtonPressed(bool mousePressed)
{
	static int mousePosX = 0, mousePosY = 0;

	SDL_GetMouseState(&mousePosX, &mousePosY);

	if (IsInCollisionBox(mousePosX, mousePosY, textureRectDouble) == true)
	{
		if (mousePressed == true)
		{
			return true;
		}
	}

	return false;

}