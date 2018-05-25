#pragma once
#include "Map_GameObject.h"

class Game{
    
public:
    
	//Game class constructor
    Game();

	//Game class deconstructor
	~Game();
    
	//Game play function
    void play();

	//Game menu function
    short menu(bool mouse_pressed);

	void editor_edit(bool mouse_pressed);
 
	bool editor_load(bool mouse_pressed);

	bool menu_settings(bool mouse_pressed);

	void player_in_borders();

	//Check and return if the player is on the ground
	bool player_is_on_ground();

	//Function to handle the collision
	void handle_player_collision();

	void resolution_changed();

private:

	//Menu

	Button button_play;
	Button button_editor;
	Button button_settings;
	Button button_quit;

	//menu_settings
	Button button_apply;
	Button button_back;

	Button button_fullhd;
	Button button_hd;

	Button label_resolution;
	Button label_fullscreen;

	TTF_Font* font_menu;
	TTF_Font* font_menu_settings;

	Texture background;

	//Editor_Menu

	Button button_new_map;
	std::vector<Button> m1map_labels;
	std::vector<std::string> m1map_paths;

	//Editor_Edit
	Button button_editor_save;
	std::string current_mappath;

	//Game
    Player player;

	Map_GameObject game_map;

	bool player_is_on_gameobject;
    
};

inline void Game::play()
{
    static Uint32 last_time = SDL_GetTicks();
    
    if(m1::key_is_pressed(SDL_SCANCODE_SPACE) && player_is_on_ground())
    {
        player.jump();
		player_is_on_gameobject = false;
    }
    
    player.fall(SDL_GetTicks() - last_time);

	player.player_walk();

	player_in_borders();

	handle_player_collision();
    
	background.render_texture(0, 0);

    player.render_object();
    
	game_map.render_map();

    last_time = SDL_GetTicks();

}

inline short Game::menu(bool mouse_pressed)
{

	background.render_texture(0, 0);
	button_play.render();
	button_editor.render();
	button_settings.render();
	button_quit.render();

	button_play.mouse_on_button();
	button_quit.mouse_on_button();
	button_editor.mouse_on_button();
	button_settings.mouse_on_button();

	if (button_play.button_pressed(mouse_pressed) == true)
	{
		return 2;
	}

	
	else if ( button_quit.button_pressed(mouse_pressed) == true )
	{
		return -1;
	}

	
	else if (button_editor.button_pressed(mouse_pressed) == true)
	{
		return 4;
	}

	
	else if (button_settings.button_pressed(mouse_pressed) == true)
	{
		return 1;
	}

	else
	{
		return 0;
	}

}


inline void Game::editor_edit(bool mouse_pressed)
{
	background.render_texture(0, 0);
	game_map.render_map();

	button_editor_save.mouse_on_button();
	button_editor_save.render();

	if (button_editor_save.button_pressed(mouse_pressed) == true)
	{
		game_map.save_map(current_mappath.c_str());
	}

}

inline bool Game::editor_load(bool mouse_pressed)
{
	background.render_texture(0, 0);
	button_new_map.mouse_on_button();
	button_new_map.render();

	static int l = 0;
	l = 0;

	for (auto i = m1map_labels.begin(); i != m1map_labels.end(); ++i)
	{

		i->mouse_on_button();
		i->render();
		if (i->button_pressed(mouse_pressed) == true)
		{
			game_map.load_map( m1map_paths.at(l).c_str() );
			current_mappath = m1map_paths.at(l);

			return 1;
		}

		++l;
	}

	return 0;

}

inline bool Game::menu_settings(bool mouse_pressed)
{
	background.render_texture(0, 0);

	label_resolution.mouse_on_button();
	button_fullhd.mouse_on_button();
	button_apply.mouse_on_button();
	button_fullhd.mouse_on_button();
	button_hd.mouse_on_button();
	button_back.mouse_on_button();

	label_resolution.render();
	label_fullscreen.render();
	button_apply.render();
	button_fullhd.render();
	button_hd.render();
	button_back.render();



	if (button_apply.button_pressed(mouse_pressed) == true)
	{
		_get_base->sync_settings();
		resolution_changed();
	}

	else if (button_fullhd.button_pressed(mouse_pressed) == true)
	{
		_get_base->set_resolution(1920, 1080);
		SDL_SetTextureAlphaMod(button_fullhd.get_texture(), 128);
		SDL_SetTextureAlphaMod(button_hd.get_texture(), 255);
	}

	else if (button_hd.button_pressed(mouse_pressed) == true)
	{
		_get_base->set_resolution(1280, 720);
		SDL_SetTextureAlphaMod(button_hd.get_texture(), 128);
		SDL_SetTextureAlphaMod(button_fullhd.get_texture(), 255);
	}

	else if (label_fullscreen.button_pressed(mouse_pressed) == true)
	{
		if (_get_base->check_if_fullscreen() == true)
		{
			label_fullscreen.init_texture_from_text("Fullscreen: Off", font_menu_settings);
			_get_base->set_fullscreen(false);
		}

		else
		{
			label_fullscreen.init_texture_from_text("Fullscreen: On", font_menu_settings);
			_get_base->set_fullscreen(true);
		}
	}

	else if ( button_back.button_pressed(mouse_pressed) == true)
	{
		return true;
	}

	return false;
}

inline bool Game::player_is_on_ground()
{
    if(player.get_rect().y + player.get_rect().h >= _SCREEN_HEIGHT || player_is_on_gameobject == true)
    {
        return true;
    }

    else
    {
        return false;
    }
}

inline void Game::player_in_borders()
{
	if (player.get_rect().x < 0) 
	{
		player.move_object_direct(0, player.get_rect().y);
	}

	else if (player.get_rect().x > _SCREEN_WIDTH - player.get_rect().w)
	{
		player.move_object_direct(_SCREEN_WIDTH - player.get_rect().w, player.get_rect().y);
	}

	if (player.get_rect().y < 0)
	{
		player.move_object_direct(player.get_rect().x, 0);
	}

	else if (player.get_rect().y > _SCREEN_HEIGHT - player.get_rect().h)
	{
		player.move_object_direct(player.get_rect().x, _SCREEN_HEIGHT - player.get_rect().h);
	}


}

inline void Game::handle_player_collision()
{
	for (auto it = game_map.get_map_objects().begin(); it != game_map.get_map_objects().end(); ++it)
	{

		switch (collision_detection(player.get_rect(), it->get_rect()))
		{

			case Bot:	player.reset_velocity();
						player.move_object_direct(player.get_rect().x, it->get_rect().y + it->get_rect().h + 1);
						break;

			case Top:	player.move_object_direct(player.get_rect().x, it->get_rect().y - player.get_rect().h);
						player_is_on_gameobject = true;
						break;

			case Left:	player.move_object_direct(it->get_rect().x - player.get_rect().w, player.get_rect().y);
						break;

			case Right: player.move_object_direct(it->get_rect().x + it->get_rect().w, player.get_rect().y);
						break;

			default: break;	

		}

	}

}

