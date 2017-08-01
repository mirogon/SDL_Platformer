#pragma once
#include "Base.h"

extern float SCALE_W;
extern float SCALE_H;

class C_Texture{

public:

//METHODS

//Texture class constructor
C_Texture();

//Texture class deconstructor
virtual ~C_Texture();

//Function to init the texture from an image
bool InitTexture (std::string path, float scale_w = SCALE_W, float scale_h = SCALE_H);
/*bool InitTextureFromText(std::string text, float scale = (SCALE_W + SCALE_H) / 2 , SDL_Color = {0,0,0,0});*/

//Free the texture from the current image
void FreeTexture ();

//INLINE

//Render the texture at x/y
void RenderTexture (int x, int y);

//Render the clip from the texture at x/y
void RenderTexture (int x, int y, SDL_Rect* clip);

//Render the clip from the texture on the clip of the screen at x/y
void RenderTexture(int x, int y, SDL_Rect* clip, SDL_Rect* clip1);

//Render the clip from the texture at x/y with a rotation of degree
void RenderTextureRotated(int x, int y, SDL_Rect* clip, double degree = 0);

//Return the current texture rect
const SDL_Rect* GetRect();

//Return the current texture
SDL_Texture* GetTexture(){

    return texture;

}

protected:

SDL_Rect* textureRect;
SDL_Texture* texture;

};

inline void C_Texture::RenderTexture(int x, int y)
{

    textureRect->x = x;
    textureRect->y = y;

    SDL_RenderCopy(_GetRenderer, texture, NULL, textureRect);

}


inline void C_Texture::RenderTexture(int x, int y, SDL_Rect* clip)
{

    textureRect->x = x;
    textureRect->y = y;

    SDL_RenderCopy(_GetRenderer, texture, clip, textureRect);

}

inline void C_Texture::RenderTexture(int x, int y, SDL_Rect* clip, SDL_Rect* clip2)
{

    textureRect->x = x;
    textureRect->y = y;

    SDL_RenderCopy(_GetRenderer, texture, clip, clip2);

}

inline void C_Texture::RenderTextureRotated(int x, int y, SDL_Rect* clip, double degree)
{

    textureRect->x = x;
    textureRect->y = y;

    SDL_RenderCopyEx(_GetRenderer, texture, clip, textureRect, degree, NULL, SDL_FLIP_NONE);

}

inline const SDL_Rect* C_Texture::GetRect()
{
    return textureRect;
}
