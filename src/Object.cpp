#include "Object.h"

C_Object::~C_Object()
{
    
}

void C_Object::Init(std::string path)
{
    C_Texture::Init(path);
    textureRectDouble.w = textureRect.w;
    textureRectDouble.h = textureRect.h;
}

void C_Object::Init(SDL_Texture* newTexture, double_Rect& newRect)
{
	FreeTexture();
	texture = newTexture;
	textureRectDouble = newRect;
}

void C_Object::MoveObjectDirect(int x, int y)
{
    textureRectDouble.x = x;
    textureRectDouble.y = y;

}

void C_Object::MoveObjectDirect(const double_Rect& newPos)
{
	textureRectDouble = newPos;
}