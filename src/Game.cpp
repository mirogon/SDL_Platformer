#include "Game.h"

C_Game::C_Game()
{
	gameObjects.push_back(C_GameObject(0));
	gameObjects[0].MoveGameObjectDirect(SCREEN_WIDTH / 2 - gameObjects[0].GetGameObjectRect().w / 2, SCREEN_HEIGHT - gameObjects[0].GetGameObjectRect().h );
	
	player.MoveObjectDirect(SCREEN_WIDTH / 2 - player.GetObjectRect().w / 2, SCREEN_HEIGHT - player.GetObjectRect().h);
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

	background.InitTexture(_BackgroundPath);
	
	
	//Menu buttons
	playButton.InitTextureFromText("Play", menuFont);
	editorButton.InitTextureFromText("Map Editor", menuFont);
	settingsButton.InitTextureFromText("Settings", menuFont);
	quitButton.InitTextureFromText("Quit", menuFont);
	
	//Menu_Settings buttons
	resolutionLabel.InitTextureFromText("Resolution:", menu_SettingsFont);
	fullscreenLabel.InitTextureFromText("Fullscreen: On", menu_SettingsFont);
	applyButton.InitTextureFromText("Apply", menu_SettingsFont);
	currentResolution.InitTextureFromText(m1::to_string(SCREEN_WIDTH) + "x" + m1::to_string(SCREEN_HEIGHT), menu_SettingsFont);
	lowerResolution.InitTextureFromText("1280x720", menu_SettingsFont);
}

C_Game::~C_Game()
{

	std::vector<C_GameObject>().swap(gameObjects);
	TTF_CloseFont(menuFont);
	TTF_CloseFont(menu_SettingsFont);

}
