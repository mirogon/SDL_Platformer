#include "Texture.h"

C_Texture::C_Texture()
{
    textureRect = new SDL_Rect;
    textureRect->x = 0;
    textureRect->y = 0;
    textureRect->w = 0;
    textureRect->h = 0;

    texture = nullptr;

}

C_Texture::~C_Texture()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(this->texture);
		texture = nullptr;
	}
  
	m1::SafeDelete(textureRect);

}

void C_Texture::FreeTexture()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
		texture = nullptr;
    }
}

bool C_Texture::Init(std::string path, float scale_w, float scale_h)
{
    
    FreeTexture();
    
    SDL_Surface* surface = IMG_Load(path.c_str());
    
    if(surface==nullptr)
    {
        m1::Log("Surface could not be created (Texture.cpp) ");
    }
    
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255) );

    texture = SDL_CreateTextureFromSurface( _GetRenderer , surface );
    if(texture == nullptr)
    {
        m1::Log("Texture could not be created (Texture.cpp)");
    }
    
    textureRect->w =  (surface->w * scale_w);
    textureRect->h =  (surface->h * scale_h);

	m1::Log("Texture created with w: " + m1::to_string(textureRect->w) + " h:" + m1::to_string(textureRect->h));
	m1::Log("TextureScale: " + m1::to_string(scale_w) + "x" + m1::to_string(scale_h));


    SDL_FreeSurface(surface);
	surface = nullptr;

    return texture != nullptr;

}

bool C_Texture::InitTextureFromText(std::string text, TTF_Font* font, SDL_Color color, float scale_w , float scale_h) {

    FreeTexture();

    SDL_Surface* loadText = TTF_RenderText_Solid(font, text.c_str(), color);
    if(loadText==nullptr){

        std::cout<<"TTF Surface konnte nicht erstellt werden"<<std::endl;

    }

    SDL_SetColorKey(loadText, SDL_TRUE, SDL_MapRGB(loadText->format, 0, 255, 255));

    texture = SDL_CreateTextureFromSurface(_GetRenderer, loadText);

    textureRect->w = loadText->w * scale_w;
    textureRect->h = loadText->h * scale_h;

    SDL_FreeSurface(loadText);

    return texture != nullptr;

}
