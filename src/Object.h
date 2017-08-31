#pragma once
#include "Texture.h"


class C_Object : public C_Texture{

public:


//METHODS

//Object class constructor
C_Object() = default;

//Object class deconstructor
virtual ~C_Object();

//Init the object with the image at path
virtual void Init(std::string path);

//Move the player to x/y
void MoveObjectDirect(int x, int y);

//INLINE

//Return the current object rect
const double_Rect& GetObjectRect() const;

//Move the player +x/+y from the current position
void MoveObject(double x, double y);

//Render the object at the current position
void RenderObject();

//Render the clip of the object texture at the current position
void RenderObject(const SDL_Rect& imageRect);

protected:

double_Rect textureRectDouble;

}; // CLASS

inline void C_Object::MoveObject(double x, double y)
{
    textureRectDouble.x += x;
    textureRectDouble.y += y;
}

inline void C_Object::RenderObject()
{
    textureRect->x = textureRectDouble.x;
    textureRect->y = textureRectDouble.y;

    SDL_RenderCopy(_GetRenderer, this->texture, NULL, textureRect);
}

inline void C_Object::RenderObject(const SDL_Rect& imageRect)
{
	textureRect->x = textureRectDouble.x;
	textureRect->y = textureRectDouble.y;

	SDL_RenderCopy(_GetRenderer, this->texture, &imageRect, textureRect);
}

inline const double_Rect& C_Object::GetObjectRect() const
{
    return textureRectDouble;
}

