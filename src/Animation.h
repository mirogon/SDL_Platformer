#pragma once

#include "Object.h"

class C_Animation : public C_Object
{

private:

	int animationLenght;

	short spriteWidth;
	short spriteHeight;

	int currentPosition;

public:

	void NextPosition();
	void RenderAnimation();

	C_Animation() = delete;
	C_Animation(std::string path, int animationLenght, short spriteWidth, short spriteHeight);
	~C_Animation() = default;

};

inline void C_Animation::NextPosition()
{
	if (currentPosition == animationLenght) 
	{
		currentPosition = 1;
	}

	else
	{
		++currentPosition;
	}

}

inline void C_Animation::RenderAnimation()
{
	
}