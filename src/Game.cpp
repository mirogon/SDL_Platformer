#include "Game.h"


C_Game::C_Game()
{
	gameMap.NewObject(Dirt, double_Coordinate());
	gameMap.GetMapObjects().back().MoveDirect(_SCREEN_WIDTH / 2 - gameMap.GetMapObjects().back().GetRect().w / 2, _SCREEN_HEIGHT - gameMap.GetMapObjects().back().GetRect().h);
	gameMap.NewObject(Dirt, double_Coordinate());
	gameMap.GetMapObjects().back().MoveDirect(_SCREEN_WIDTH / 2 - gameMap.GetMapObjects().back().GetRect().w / 2, _SCREEN_HEIGHT / 2);


	gameMap.SaveMap("../data/m1map/savetest.m1map");
	gameMap.LoadMap("../data/m1map/savetest.m1map");

	player.MoveObjectDirect(_SCREEN_WIDTH / 2 - player.GetRect().w / 2, _SCREEN_HEIGHT - player.GetRect().h);
	playerIsOnGameObject = false;


	menuFont = TTF_OpenFont(_MenuFontPath, 90);
	if (menuFont == nullptr)
	{
		m1::Log("menuFont could not be intialized ( Game.cpp )");
	}
	menu_SettingsFont = TTF_OpenFont(_MenuFontPath, 60);
	if (menuFont == nullptr)
	{
		m1::Log("menu_SettingsFont could not be intialized ( Game.cpp )");
	}

	background.Init(_BackgroundPath);
	
	
	//Menu buttons

	playButton.Init("Play", *menuFont);
	playButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - playButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.2 - playButton.GetRect().h / 2);
	editorButton.Init("Map Editor", *menuFont);
	editorButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - editorButton.GetRect().w / 2, _SCREEN_HEIGHT *0.4 - editorButton.GetRect().h / 2);
	settingsButton.Init("Settings", *menuFont );
	settingsButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - settingsButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.6 - settingsButton.GetRect().h / 2);
	quitButton.Init("Quit", *menuFont);
	quitButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - quitButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.8 - quitButton.GetRect().h / 2);

	//Menu_Settings buttons
	resolutionLabel.Init("Resolution:", *menu_SettingsFont);
	resolutionLabel.MoveObjectDirect(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.15);
	fullscreenLabel.Init("Fullscreen: On", *menu_SettingsFont);
	fullscreenLabel.MoveObjectDirect(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.8);

	backButton.Init("Back", *menu_SettingsFont);
	backButton.MoveObjectDirect( 0, _SCREEN_HEIGHT - backButton.GetRect().h);
	applyButton.Init("Apply", *menu_SettingsFont);
	applyButton.MoveObjectDirect( _SCREEN_WIDTH - applyButton.GetRect().w, _SCREEN_HEIGHT - applyButton.GetRect().h);
	fullHdResolution.Init("1920x1080", *menu_SettingsFont);
	fullHdResolution.MoveObjectDirect(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.15);
	hdResolution.Init("1280x720", *menu_SettingsFont);
	hdResolution.MoveObjectDirect(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.3);

	//Editor_Menu Buttons
	newMapButton.Init("New Map", *menuFont );
	newMapButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - newMapButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.1);

}

C_Game::~C_Game()
{
	TTF_CloseFont(menuFont);
	menuFont = nullptr;
	TTF_CloseFont(menu_SettingsFont);
	menu_SettingsFont = nullptr;
}

void C_Game::ResolutionChanged()
{


	//Menu buttons

	playButton.Init("Play", *menuFont);
	playButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - playButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.2 - playButton.GetRect().h / 2);
	editorButton.Init("Map Editor", *menuFont);
	editorButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - editorButton.GetRect().w / 2, _SCREEN_HEIGHT *0.4 - editorButton.GetRect().h / 2);
	settingsButton.Init("Settings", *menuFont);
	settingsButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - settingsButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.6 - settingsButton.GetRect().h / 2);
	quitButton.Init("Quit", *menuFont);
	quitButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - quitButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.8 - quitButton.GetRect().h / 2);

	//Menu_Settings buttons
	resolutionLabel.Init("Resolution:", *menu_SettingsFont);
	resolutionLabel.MoveObjectDirect(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.15);
	fullscreenLabel.Init("Fullscreen: On", *menu_SettingsFont);
	fullscreenLabel.MoveObjectDirect(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.8);

	backButton.Init("Back", *menu_SettingsFont);
	backButton.MoveObjectDirect(0, _SCREEN_HEIGHT - backButton.GetRect().h);
	applyButton.Init("Apply", *menu_SettingsFont);
	applyButton.MoveObjectDirect(_SCREEN_WIDTH - applyButton.GetRect().w, _SCREEN_HEIGHT - applyButton.GetRect().h);
	fullHdResolution.Init("1920x1080", *menu_SettingsFont);
	fullHdResolution.MoveObjectDirect(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.15);
	hdResolution.Init("1280x720", *menu_SettingsFont);
	hdResolution.MoveObjectDirect(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.3);

	//Editor_Menu Buttons
	newMapButton.Init("New Map", *menuFont);
	newMapButton.MoveObjectDirect(_SCREEN_WIDTH / 2 - newMapButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.1);

	if (_GetBase->IsFullscreen() == true)
	{
		fullscreenLabel.Init("Fullscreen: On", *menu_SettingsFont);
	}
	else
	{
		fullscreenLabel.Init("Fullscreen: Off", *menu_SettingsFont);
	}

	backButton.InitTextureFromText("Back", menu_SettingsFont);

	background.Init(_BackgroundPath);

	player.Init(_PlayerPath);

	gameMap.ClearMap();
	C_GameObject::InitStaticTextures();
	gameMap.NewObject(Dirt, double_Coordinate());
	gameMap.GetMapObjects().back().MoveDirect(_SCREEN_WIDTH / 2 - gameMap.GetMapObjects().back().GetRect().w / 2, _SCREEN_HEIGHT - gameMap.GetMapObjects().back().GetRect().h);
	gameMap.NewObject(Dirt, double_Coordinate());
	gameMap.GetMapObjects().back().MoveDirect(_SCREEN_WIDTH / 2 - gameMap.GetMapObjects().back().GetRect().w / 2, _SCREEN_HEIGHT / 2);
}