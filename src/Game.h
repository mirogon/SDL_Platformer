#pragma once
#include "Map_GameObject.h"

class Game
{
    
public:
    
	//Game class constructor
    Game();

	//Game class deconstructor
	~Game();
    
	//Game play function
    void play();

	//Game menu function
    short menu(bool mouse_pressed);

	void editor_edit(bool left_mousebutton_pressed, bool right_mousebutton_pressed);
 
	bool editor_load(bool mouse_pressed);

	bool menu_settings(bool mouse_pressed);

	void player_in_borders();

	//Check and return if the player is on the ground
	bool player_is_on_ground();

	//Function to handle the collision
	void handle_player_collision();

	void resolution_changed();

private:

	bool editor_load_newmap();
	
	void sync_available_maps();

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
	std::vector<Button> selectable_blocks;

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

inline void Game::editor_edit(bool left_mousebutton_pressed, bool right_mousebutton_pressed)
{
	static GameObject current_selected_block = GameObject(-1);
	static bool hud_is_active = true;
	static m1::key_pressed_and_released h_pr{SDL_SCANCODE_H};

	if( h_pr() == true)
	{
		hud_is_active = !hud_is_active;	
	}

	//Render background and map
	background.render_texture(0, 0);
	game_map.render_map();

	//Save button handling
	if(hud_is_active == true)
	{
		button_editor_save.mouse_on_button();
		button_editor_save.render();
	
		if (button_editor_save.button_pressed(left_mousebutton_pressed) == true)
		{
			game_map.save_map(current_mappath.c_str());
		}
	}

	//Select block in hud
	static int mousepos_x;
	static int mousepos_y;
	SDL_GetMouseState(&mousepos_x, &mousepos_y);

	unsigned int f_i = 0;
	if(hud_is_active == true)
	{
		for(auto i = selectable_blocks.begin(); i != selectable_blocks.end(); ++i)
		{
			i->mouse_on_button();
			i->render();

			if(i->button_pressed(left_mousebutton_pressed) == true)
			{
				current_selected_block.init(f_i, { 0, 0 } );
			}
		
			++f_i;
		}
	}

	//Place blocks
	if(current_selected_block.get_block_type() != m1::E_BlockType::NONE)
	{
		current_selected_block.move_direct( {mousepos_x, mousepos_y} );
		current_selected_block.render();

		if(left_mousebutton_pressed == true && hud_is_active == false)
		{
			game_map.new_object( current_selected_block.get_block_type(), {current_selected_block.get_rect().x, current_selected_block.get_rect().y} );
		}
	}

	//Remove blocks
	SDL_GetMouseState(&mousepos_x, &mousepos_y);
	for(int i = 0; i < game_map.get_map_objects().size(); ++i)
	{
		static std::vector<GameObject>::iterator it = game_map.get_map_objects().begin() + i;
		it = game_map.get_map_objects().begin() + i;

		if ( m1::is_in_collision_box( mousepos_x, mousepos_y, it->get_rect() ) == true )
		{
			if(right_mousebutton_pressed == true)
			{
				game_map.remove_object(it);
			}
		}

	}

}

inline bool Game::editor_load(bool left_mousebutton_pressed)
{
	static bool creating_new_map = false;
	background.render_texture(0, 0);
	button_new_map.mouse_on_button();
	button_new_map.render();

	if(button_new_map.button_pressed(left_mousebutton_pressed) == true)
	{	
		creating_new_map = true;
	}
	
	if(creating_new_map == true)
	{
		if(editor_load_newmap() == true)
		{
			creating_new_map = false;
			sync_available_maps();
		}
	}
	
	else
	{
		static int l = 0;
		l = 0;
		for (auto i = m1map_labels.begin(); i != m1map_labels.end(); i++)
		{
			i->mouse_on_button();
			i->render();
			if (i->button_pressed(left_mousebutton_pressed) == true)
			{
				game_map.load_map( m1map_paths.at(l).c_str() );
				current_mappath = m1map_paths.at(l);

				return 1;
			}

			++l;
		}
	}
	
	return 0;

}

inline bool Game::editor_load_newmap()
{
	static Texture label_enter_mapname;
	static Texture label_input;
	static std::string input_text;
	static bool first_time = true;
	
	if(first_time == true)
	{
		first_time = false;
		
		label_enter_mapname.init_texture_from_text("Enter mapname:", font_menu);
	}
	
	SDL_Event e;
	SDL_StartTextInput();
	while(SDL_PollEvent(&e) != 0)
	{	
		if(e.type == SDL_KEYDOWN)
		{
			if(e.key.keysym.sym == SDLK_BACKSPACE && input_text.size() > 0)
			{ 
				input_text.pop_back();
			}
			
			if(e.key.keysym.sym == SDLK_RETURN)
			{
				std::string filename = "../data/m1map/";
				filename+= input_text;
				filename+= ".m1map";
				std::ofstream o(filename.c_str(), std::ios::out | std::ios::trunc);
				o.close();
				
				return true;
			}
		}
		
		else if(e.type == SDL_TEXTINPUT)
		{
			input_text += e.text.text;
		}
		
	}
	SDL_StopTextInput();
	
	if(input_text.size() >0)
	{
		label_input.init_texture_from_text(input_text, font_menu);
	}
	
	background.render_texture(0,0);
	
	label_input.render_texture(_SCREEN_WIDTH / 2 , _SCREEN_HEIGHT / 2);
	
	return false;
	
	
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

