#pragma once
#include "Texture.h"


class Object : public Texture{

public:


//METHODS

//Object class constructor
Object() = default;

//Object class deconstructor
virtual ~Object();

//init the object with the image at path
virtual void init(std::string path);

virtual void init(SDL_Texture* new_texture, double_Rect& new_rect);

//move the player to x/y
void move_object_direct(int x, int y);

void move_object_direct(const double_Coordinate& new_pos);

//INLINE

//Return the current object rect
const double_Rect& get_rect() const;

//move the player +x/+y from the current position
void move_object(double x, double y);

//render the object at the current position
void render_object();

//render the clip of the object texture at the current position
void render_object(const SDL_Rect& image_rect);

protected:

double_Rect texture_rect_double;

}; // CLASS

inline void Object::move_object(double x, double y)
{
    texture_rect_double.x += x;
    texture_rect_double.y += y;
}

inline void Object::render_object()
{
    texture_rect.x = texture_rect_double.x;
    texture_rect.y = texture_rect_double.y;

    SDL_RenderCopy(_get_renderer, this->texture, NULL, &texture_rect);
}

inline void Object::render_object(const SDL_Rect& image_rect)
{
	texture_rect.x = texture_rect_double.x;
	texture_rect.y = texture_rect_double.y;

	SDL_RenderCopy(_get_renderer, this->texture, &image_rect, &texture_rect);
}

inline const double_Rect& Object::get_rect() const
{
    return texture_rect_double;
}

