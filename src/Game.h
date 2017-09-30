#pragma once
#include "Map_GameObject.h"

class C_Game{
    
public:
    
	//Game class constructor
    C_Game();

	//Game class deconstructor
	~C_Game();
    
	//Game play function
    void Game_Play();

	//Game menu function
    short Game_Menu(bool mousePressed);

	void Game_Editor_Edit(bool mousePressed);
 
	bool Game_Editor_Load(bool mousePressed);

	bool Game_Menu_Settings(bool mousePressed);

	void PlayerInBorders();

	//Check and return if the player is on the ground
	bool PlayerIsOnGround();

	//Function to handle the collision
	void HandlePlayerCollision();

	void ResolutionChanged();

private:

	//Menu

	C_Button playButton;
	C_Button editorButton;
	C_Button settingsButton;
	C_Button quitButton;

	//Menu_Settings
	C_Button applyButton;
	C_Button backButton;

	C_Button fullHdResolution;
	C_Button hdResolution;

	C_Button resolutionLabel;
	C_Button fullscreenLabel;

	TTF_Font* menuFont;
	TTF_Font* menu_SettingsFont;

	C_Texture background;

	//Editor_Menu

	C_Button newMapButton;
	std::vector<C_Button> m1mapLabels;
	std::vector<std::string> m1mapPaths;

	//Editor_Edit
	C_Button editorSaveButton;
	std::string currentMapPath;

	//Game
    C_Player player;

	C_Map_GameObject gameMap;

	bool playerIsOnGameObject;
    
};

inline void C_Game::Game_Play()
{
    static Uint32 lastTime = SDL_GetTicks();
    
    if(m1::KeyIsPressed(SDL_SCANCODE_SPACE) && PlayerIsOnGround())
    {
        player.Jump();
		playerIsOnGameObject = false;
    }
    
    player.Fall(SDL_GetTicks() - lastTime);

	player.PlayerWalk();

	PlayerInBorders();

	HandlePlayerCollision();
    
	background.RenderTexture(0, 0);

    player.RenderObject();
    
	gameMap.RenderMap();

    lastTime = SDL_GetTicks();

}

inline short C_Game::Game_Menu(bool mousePressed)
{

	background.RenderTexture(0, 0);
	playButton.Render();
	editorButton.Render();
	settingsButton.Render();
	quitButton.Render();

	playButton.MouseOnButton();
	quitButton.MouseOnButton();
	editorButton.MouseOnButton();
	settingsButton.MouseOnButton();

	if (playButton.ButtonPressed(mousePressed) == true)
	{
		return 2;
	}

	
	else if ( quitButton.ButtonPressed(mousePressed) == true )
	{
		return -1;
	}

	
	else if (editorButton.ButtonPressed(mousePressed) == true)
	{
		return 4;
	}

	
	else if (settingsButton.ButtonPressed(mousePressed) == true)
	{
		return 1;
	}

	else
	{
		return 0;
	}

}


inline void C_Game::Game_Editor_Edit(bool mousePressed)
{
	background.RenderTexture(0, 0);
	gameMap.RenderMap();

	editorSaveButton.MouseOnButton();
	editorSaveButton.Render();

	if (editorSaveButton.ButtonPressed(mousePressed) == true)
	{
		gameMap.SaveMap(currentMapPath.c_str());
	}

}

inline bool C_Game::Game_Editor_Load(bool mousePressed)
{
	background.RenderTexture(0, 0);
	newMapButton.MouseOnButton();
	newMapButton.Render();

	static int l = 0;
	l = 0;

	for (auto i = m1mapLabels.begin(); i != m1mapLabels.end(); ++i)
	{

		i->MouseOnButton();
		i->Render();
		if (i->ButtonPressed(mousePressed) == true)
		{
			gameMap.LoadMap( m1mapPaths.at(l).c_str() );
			currentMapPath = m1mapPaths.at(l);

			return 1;
		}

		++l;
	}

	return 0;

}

inline bool C_Game::Game_Menu_Settings(bool mousePressed)
{
	background.RenderTexture(0, 0);

	resolutionLabel.MouseOnButton();
	fullHdResolution.MouseOnButton();
	applyButton.MouseOnButton();
	fullHdResolution.MouseOnButton();
	hdResolution.MouseOnButton();
	backButton.MouseOnButton();

	resolutionLabel.Render();
	fullscreenLabel.Render();
	applyButton.Render();
	fullHdResolution.Render();
	hdResolution.Render();
	backButton.Render();



	if (applyButton.ButtonPressed(mousePressed) == true)
	{
		_GetBase->SyncSettings();
		ResolutionChanged();
	}

	else if (fullHdResolution.ButtonPressed(mousePressed) == true)
	{
		_GetBase->SetResolution(1920, 1080);
		SDL_SetTextureAlphaMod(fullHdResolution.GetTexture(), 128);
		SDL_SetTextureAlphaMod(hdResolution.GetTexture(), 255);
	}

	else if (hdResolution.ButtonPressed(mousePressed) == true)
	{
		_GetBase->SetResolution(1280, 720);
		SDL_SetTextureAlphaMod(hdResolution.GetTexture(), 128);
		SDL_SetTextureAlphaMod(fullHdResolution.GetTexture(), 255);
	}

	else if (fullscreenLabel.ButtonPressed(mousePressed) == true)
	{
		if (_GetBase->IsFullscreen() == true)
		{
			fullscreenLabel.InitTextureFromText("Fullscreen: Off", menu_SettingsFont);
			_GetBase->SetFullscreen(false);
		}

		else
		{
			fullscreenLabel.InitTextureFromText("Fullscreen: On", menu_SettingsFont);
			_GetBase->SetFullscreen(true);
		}
	}

	else if ( backButton.ButtonPressed(mousePressed) == true)
	{
		return true;
	}

	return false;
}

inline bool C_Game::PlayerIsOnGround()
{
    if(player.GetRect().y + player.GetRect().h >= _SCREEN_HEIGHT || playerIsOnGameObject == true)
    {
        return true;
    }

    else
    {
        return false;
    }
}

inline void C_Game::PlayerInBorders()
{
	if (player.GetRect().x < 0) 
	{
		player.MoveObjectDirect(0, player.GetRect().y);
	}

	else if (player.GetRect().x > _SCREEN_WIDTH - player.GetRect().w)
	{
		player.MoveObjectDirect(_SCREEN_WIDTH - player.GetRect().w, player.GetRect().y);
	}

	if (player.GetRect().y < 0)
	{
		player.MoveObjectDirect(player.GetRect().x, 0);
	}

	else if (player.GetRect().y > _SCREEN_HEIGHT - player.GetRect().h)
	{
		player.MoveObjectDirect(player.GetRect().x, _SCREEN_HEIGHT - player.GetRect().h);
	}


}

inline void C_Game::HandlePlayerCollision()
{
	for (auto iT = gameMap.GetMapObjects().begin(); iT != gameMap.GetMapObjects().end(); ++iT)
	{

		switch (CollisionDetection(player.GetRect(), iT->GetRect()))
		{

			case Bot:	player.ResetVelocity();
						player.MoveObjectDirect(player.GetRect().x, iT->GetRect().y + iT->GetRect().h + 1);
						break;

			case Top:	player.MoveObjectDirect(player.GetRect().x, iT->GetRect().y - player.GetRect().h);
						playerIsOnGameObject = true;
						break;

			case Left:	player.MoveObjectDirect(iT->GetRect().x - player.GetRect().w, player.GetRect().y);
						break;

			case Right: player.MoveObjectDirect(iT->GetRect().x + iT->GetRect().w, player.GetRect().y);
						break;

			default: break;	

		}

	}

}

