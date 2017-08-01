#include "Object.h"

C_Object::~C_Object()
{
    
}

void C_Object::InitObject(std::string path)
{
    InitTexture(path);
    textureRectDouble.w = textureRect->w;
    textureRectDouble.h = textureRect->h;
}



void C_Object::MoveObjectDirect(int x, int y)
{
    textureRectDouble.x = x;
    textureRectDouble.y = y;

}