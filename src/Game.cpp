#include "Game.h"


Game::Game()
{
	/*
	game_map.new_object(DIRT, double_Coordinate());
	game_map.get_map_objects().back().move_direct(_SCREEN_WIDTH / 2 - game_map.get_map_objects().back().get_rect().w / 2, _SCREEN_HEIGHT - game_map.get_map_objects().back().get_rect().h);
	game_map.new_object(DIRT, double_Coordinate());
	game_map.get_map_objects().back().move_direct(_SCREEN_WIDTH / 2 - game_map.get_map_objects().back().get_rect().w / 2, _SCREEN_HEIGHT / 2);

	game_map.save_map("../data/m1map/savetest.m1map");
	*/
	game_map.load_map("../data/m1map/savetest.m1map");

	player.move_object_direct(_SCREEN_WIDTH / 2 - player.get_rect().w / 2, _SCREEN_HEIGHT - player.get_rect().h);
	player_is_on_gameobject = false;


	font_menu = TTF_OpenFont(_PATH_MENU_FONT, 90);
	if (font_menu == nullptr)
	{
		m1::log("font_menu could not be intialized ( Game.cpp )");
	}
	font_menu_settings = TTF_OpenFont(_PATH_MENU_FONT, 60);
	if (font_menu == nullptr)
	{
		m1::log("font_menu_settings could not be intialized ( Game.cpp )");
	}

	background.init(_PATH_BACKGROUND);
	
	
	//Menu buttons

	button_play.init("Play", *font_menu);
	button_play.move_object_direct(_SCREEN_WIDTH / 2 - button_play.get_rect().w / 2, _SCREEN_HEIGHT * 0.2 - button_play.get_rect().h / 2);
	button_editor.init("Map Editor", *font_menu);
	button_editor.move_object_direct(_SCREEN_WIDTH / 2 - button_editor.get_rect().w / 2, _SCREEN_HEIGHT *0.4 - button_editor.get_rect().h / 2);
	button_settings.init("Settings", *font_menu );
	button_settings.move_object_direct(_SCREEN_WIDTH / 2 - button_settings.get_rect().w / 2, _SCREEN_HEIGHT * 0.6 - button_settings.get_rect().h / 2);
	button_quit.init("Quit", *font_menu);
	button_quit.move_object_direct(_SCREEN_WIDTH / 2 - button_quit.get_rect().w / 2, _SCREEN_HEIGHT * 0.8 - button_quit.get_rect().h / 2);

	//menu_settings buttons
	label_resolution.init("Resolution:", *font_menu_settings);
	label_resolution.move_object_direct(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.15);
	label_fullscreen.init("Fullscreen: On", *font_menu_settings);
	label_fullscreen.move_object_direct(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.8);

	button_back.init("Back", *font_menu_settings);
	button_back.move_object_direct( 0, _SCREEN_HEIGHT - button_back.get_rect().h);
	button_apply.init("Apply", *font_menu_settings);
	button_apply.move_object_direct( _SCREEN_WIDTH - button_apply.get_rect().w, _SCREEN_HEIGHT - button_apply.get_rect().h);
	button_fullhd.init("1920x1080", *font_menu_settings);
	button_fullhd.move_object_direct(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.15);
	button_hd.init("1280x720", *font_menu_settings);
	button_hd.move_object_direct(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.3);

	//Editor_Menu Buttons
	button_new_map.init("New Map", *font_menu );
	button_new_map.move_object_direct(_SCREEN_WIDTH / 2 - button_new_map.get_rect().w / 2, _SCREEN_HEIGHT * 0.1);

	//Editor_Edit Buttons
	button_editor_save.init("Save", *font_menu_settings);
	button_editor_save.move_object_direct(_SCREEN_WIDTH - button_editor_save.get_rect().w, _SCREEN_HEIGHT - button_editor_save.get_rect().h);

	selectable_blocks.push_back( Button() );
	selectable_blocks.back().Object::init(std::string(_PATH_DIRT));
	selectable_blocks.back().move_object_direct({0,0});

	static int l = 0;
	l = 0;

	for (auto i : std::experimental::filesystem::directory_iterator("../data/m1map"))
	{
		m1map_labels.push_back(Button());
		m1map_labels.back().init(i.path().string().c_str(), *font_menu_settings);
		m1map_labels.back().move_object_direct( _SCREEN_WIDTH / 2 - m1map_labels.back().get_rect().w / 2, _SCREEN_HEIGHT * ( 0.1 * ( l + 3) ) );
		m1map_paths.push_back(std::string(i.path().string()));

		++l;
	}
}

Game::~Game()
{
	TTF_CloseFont(font_menu);
	font_menu = nullptr;
	TTF_CloseFont(font_menu_settings);
	font_menu_settings = nullptr;
}

void Game::resolution_changed()
{

	//Menu buttons
	button_play.init("Play", *font_menu);
	button_play.move_object_direct(_SCREEN_WIDTH / 2 - button_play.get_rect().w / 2, _SCREEN_HEIGHT * 0.2 - button_play.get_rect().h / 2);
	button_editor.init("Map Editor", *font_menu);
	button_editor.move_object_direct(_SCREEN_WIDTH / 2 - button_editor.get_rect().w / 2, _SCREEN_HEIGHT *0.4 - button_editor.get_rect().h / 2);
	button_settings.init("Settings", *font_menu);
	button_settings.move_object_direct(_SCREEN_WIDTH / 2 - button_settings.get_rect().w / 2, _SCREEN_HEIGHT * 0.6 - button_settings.get_rect().h / 2);
	button_quit.init("Quit", *font_menu);
	button_quit.move_object_direct(_SCREEN_WIDTH / 2 - button_quit.get_rect().w / 2, _SCREEN_HEIGHT * 0.8 - button_quit.get_rect().h / 2);

	//menu_settings buttons
	label_resolution.init("Resolution:", *font_menu_settings);
	label_resolution.move_object_direct(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.15);
	label_fullscreen.init("Fullscreen: On", *font_menu_settings);
	label_fullscreen.move_object_direct(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.8);

	button_back.init("Back", *font_menu_settings);
	button_back.move_object_direct(0, _SCREEN_HEIGHT - button_back.get_rect().h);
	button_apply.init("Apply", *font_menu_settings);
	button_apply.move_object_direct(_SCREEN_WIDTH - button_apply.get_rect().w, _SCREEN_HEIGHT - button_apply.get_rect().h);
	button_fullhd.init("1920x1080", *font_menu_settings);
	button_fullhd.move_object_direct(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.15);
	button_hd.init("1280x720", *font_menu_settings);
	button_hd.move_object_direct(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.3);

	//Editor_Menu Buttons
	button_new_map.init("New Map", *font_menu);
	button_new_map.move_object_direct(_SCREEN_WIDTH / 2 - button_new_map.get_rect().w / 2, _SCREEN_HEIGHT * 0.1);

	//Editor_Edit Buttons
	button_editor_save.init("Save", *font_menu_settings);
	button_editor_save.move_object_direct(_SCREEN_WIDTH - button_editor_save.get_rect().w, _SCREEN_HEIGHT - button_editor.get_rect().h);

	if (_get_base->check_if_fullscreen() == true)
	{
		label_fullscreen.init("Fullscreen: On", *font_menu_settings);
	}
	else
	{
		label_fullscreen.init("Fullscreen: Off", *font_menu_settings);
	}

	button_back.init_texture_from_text("Back", font_menu_settings);

	background.init(_PATH_BACKGROUND);

	player.init(_PATH_PLAYER);

	game_map.clear_map();
	GameObject::init_static_textures();
	game_map.new_object(DIRT, double_Coordinate());
	game_map.get_map_objects().back().move_direct(_SCREEN_WIDTH / 2 - game_map.get_map_objects().back().get_rect().w / 2, _SCREEN_HEIGHT - game_map.get_map_objects().back().get_rect().h);
	game_map.new_object(DIRT, double_Coordinate());
	game_map.get_map_objects().back().move_direct(_SCREEN_WIDTH / 2 - game_map.get_map_objects().back().get_rect().w / 2, _SCREEN_HEIGHT / 2);
}