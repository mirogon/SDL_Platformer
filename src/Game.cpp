#include "Game.h"

C_Game::C_Game()
{
	dirtObjects.push_back(C_GameObject_Dirt());
	auto dirtObjectsIt = dirtObjects.begin();

	dirtObjectsIt->Init();

	dirtObjectsIt->MoveGameObjectDirect(SCREEN_WIDTH / 2 - dirtObjectsIt->GetGameObjectRect().w / 2, SCREEN_HEIGHT - dirtObjectsIt->GetGameObjectRect().h);

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
}

C_Game::~C_Game()
{
	dirtObjects.clear();
	TTF_CloseFont(menuFont);
	TTF_CloseFont(menu_SettingsFont);
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

	//Game

	player.Init(_PlayerPath);

	dirtObjects.clear();

	dirtObjects.push_back(C_GameObject_Dirt());

	auto dirtObjectsIt = dirtObjects.begin();

	dirtObjectsIt->Init();

	dirtObjectsIt->MoveGameObjectDirect(SCREEN_WIDTH / 2 - dirtObjectsIt->GetGameObjectRect().w / 2, SCREEN_HEIGHT - dirtObjectsIt->GetGameObjectRect().h);

	dirtObjectsIt->PrintGameObjectStats();
}