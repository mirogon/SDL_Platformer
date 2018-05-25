#pragma once
#include "Base.h"

class Texture{

public:

//METHODS

//Texture class constructor
Texture();

//Texture class deconstructor
virtual ~Texture();

//Function to init the texture from an image
virtual bool init (std::string path, float scale_w = _SCALE_W, float scale_h = _SCALE_H);
bool init_texture_from_text(std::string text, TTF_Font* font, SDL_Color color = SDL_Color{ 0,0,0 }, float scale_w = _SCALE_W, float scale_h = _SCALE_H);

//Free the texture from the current image
void free_texture ();

//INLINE

//render the texture at x/y
void render_texture (int x, int y);

//render the clip from the texture at x/y
void render_texture (int x, int y, SDL_Rect* clip);

//render the clip from the texture on the clip of the screen at x/y
void render_texture(int x, int y, SDL_Rect* clip, SDL_Rect* clip1);

//render the clip from the texture at x/y with a rotation of degree
void render_texture_rotated(int x, int y, SDL_Rect* clip, double degree = 0);

//Return the current texture rect
virtual const SDL_Rect get_rect();


//Return the current texture
virtual SDL_Texture* get_texture(){

    return texture;

}

protected:

SDL_Rect texture_rect;
SDL_Texture* texture;

};

inline void Texture::render_texture(int x, int y)
{

    texture_rect.x = x;
    texture_rect.y = y;

    SDL_RenderCopy(_get_renderer, texture, NULL, &texture_rect);

}


inline void Texture::render_texture(int x, int y, SDL_Rect* clip)
{

    texture_rect.x = x;
    texture_rect.y = y;

    SDL_RenderCopy(_get_renderer, texture, clip, &texture_rect);

}

inline void Texture::render_texture(int x, int y, SDL_Rect* clip, SDL_Rect* clip2)
{

    texture_rect.x = x;
    texture_rect.y = y;

    SDL_RenderCopy(_get_renderer, texture, clip, clip2);

}

inline void Texture::render_texture_rotated(int x, int y, SDL_Rect* clip, double degree)
{

    texture_rect.x = x;
    texture_rect.y = y;

    SDL_RenderCopyEx(_get_renderer, texture, clip, &texture_rect, degree, NULL, SDL_FLIP_NONE);

}

inline const SDL_Rect Texture::get_rect()
{
	if (&texture_rect == nullptr)
	{
		m1::log("texture_rect is nullptr and cannot be returned");
	}

	else
	{
		return texture_rect;
	}
}
