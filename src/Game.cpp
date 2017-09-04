#include "Game.h"


C_Game::C_Game()
{
	gameMap.NewObject(Dirt, double_Coordinate());
	gameMap.GetMapObjects().back().MoveDirect(_SCREEN_WIDTH / 2 - gameMap.GetMapObjects().back().GetRect().w / 2, _SCREEN_HEIGHT - gameMap.GetMapObjects().back().GetRect().h);
	gameMap.NewObject(Dirt, double_Coordinate());
	gameMap.GetMapObjects().back().MoveDirect(_SCREEN_WIDTH / 2 - gameMap.GetMapObjects().back().GetRect().w / 2, _SCREEN_HEIGHT / 2);


	gameMap.SaveMap("savetest.m1s");
	gameMap.LoadMap("savetest.m1s");

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
	playButton.InitTextureFromText("Play", menuFont);
	editorButton.InitTextureFromText("Map Editor", menuFont);
	settingsButton.InitTextureFromText("Settings", menuFont);
	quitButton.InitTextureFromText("Quit", menuFont);
	
	//Menu_Settings buttons
	resolutionLabel.InitTextureFromText("Resolution:", menu_SettingsFont);
	fullscreenLabel.InitTextureFromText("Fullscreen: On", menu_SettingsFont);
	backButton.InitTextureFromText("Back", menu_SettingsFont);
	applyButton.InitTextureFromText("Apply", menu_SettingsFont);
	fullHdResolution.InitTextureFromText("1920x1080", menu_SettingsFont);
	hdResolution.InitTextureFromText("1280x720", menu_SettingsFont);

	//Editor_Menu Buttons
	newMapButton.InitTextureFromText("New Map", menuFont);


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

	//Menu
	playButton.InitTextureFromText("Play", menuFont);
	editorButton.InitTextureFromText("Map Editor", menuFont);
	settingsButton.InitTextureFromText("Settings", menuFont);
	quitButton.InitTextureFromText("Quit", menuFont);

	//Menu_Settings
	applyButton.InitTextureFromText("Apply", menu_SettingsFont);
	resolutionLabel.InitTextureFromText("Resolution:", menu_SettingsFont);
	fullHdResolution.InitTextureFromText("1920x1080", menu_SettingsFont);
	hdResolution.InitTextureFromText("1280x720", menu_SettingsFont);

	if (_GetBase->IsFullscreen() == true)
	{
		fullscreenLabel.InitTextureFromText("Fullscreen: On", menu_SettingsFont);
	}
	else
	{
		fullscreenLabel.InitTextureFromText("Fullscreen: Off", menu_SettingsFont);
	}

	backButton.InitTextureFromText("Back", menu_SettingsFont);

	background.Init(_BackgroundPath);

	player.Init(_PlayerPath);

	gameMap.ClearMap();
	C_GameObject::InitStaticTextures();
	gameMap.NewObject(Dirt, double_Coordinate());
	gameMap.GetMapObjects().back().MoveDirect(_SCREEN_WIDTH / 2 - gameMap.GetMapObjects().back().GetRect().w / 2, _SCREEN_HEIGHT - gameMap.GetMapObjects().back().GetRect().h);

}