#include "Object.h"

Object::~Object()
{
    
}

void Object::init(std::string path)
{
    Texture::init(path);
    texture_rect_double.w = texture_rect.w;
    texture_rect_double.h = texture_rect.h;
}

void Object::init(SDL_Texture* new_texture, double_Rect& new_rect)
{
	free_texture();
	texture = new_texture;
	texture_rect_double = new_rect;
}

void Object::move_object_direct(int x, int y)
{
    texture_rect_double.x = x;
    texture_rect_double.y = y;

}

void Object::move_object_direct(const double_Coordinate& new_pos)
{
	texture_rect_double.x = new_pos.x;
	texture_rect_double.y = new_pos.y;
}