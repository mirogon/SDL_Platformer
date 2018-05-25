#include "Texture.h"

Texture::Texture()
{
    texture_rect.x = 0;
    texture_rect.y = 0;
    texture_rect.w = 0;
    texture_rect.h = 0;

    texture = nullptr;

}

Texture::~Texture()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(this->texture);
		texture = nullptr;
	}
  
}

void Texture::free_texture()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
		texture = nullptr;
    }
}

bool Texture::init(std::string path, float scale_w, float scale_h)
{
    
    free_texture();
    
    SDL_Surface* surface = IMG_Load(path.c_str());
    
    if(surface==nullptr)
    {
        std::string s = "Surface could not be created (Texture.cpp) " + path;

        m1::log(s);
    }
    
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255) );

    texture = SDL_CreateTextureFromSurface( _get_renderer , surface );
    if(texture == nullptr)
    {
        m1::log("Texture could not be created (Texture.cpp)");
    }
    
    texture_rect.w =  (surface->w * scale_w);
    texture_rect.h =  (surface->h * scale_h);

	m1::log("Texture created with w: " + m1::to_string(texture_rect.w) + " h:" + m1::to_string(texture_rect.h));
	m1::log("TextureScale: " + m1::to_string(scale_w) + "x" + m1::to_string(scale_h));


    SDL_FreeSurface(surface);
	surface = nullptr;

    return texture != nullptr;

}

bool Texture::init_texture_from_text(std::string text, TTF_Font* font, SDL_Color color, float scale_w , float scale_h) {

    free_texture();

    SDL_Surface* load_text = TTF_RenderText_Solid(font, text.c_str(), color);
    if(load_text==nullptr){

        std::cout<<"TTF Surface konnte nicht erstellt werden"<<std::endl;

    }

    SDL_SetColorKey(load_text, SDL_TRUE, SDL_MapRGB(load_text->format, 0, 255, 255));

    texture = SDL_CreateTextureFromSurface(_get_renderer, load_text);

    texture_rect.w = load_text->w * scale_w;
    texture_rect.h = load_text->h * scale_h;

    SDL_FreeSurface(load_text);

    return texture != nullptr;

}
