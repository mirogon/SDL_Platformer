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
 
	bool Game_Menu_Settings(bool mousePressed);

	void PlayerInBorders();

	//Check and return if the player is on the ground
	bool PlayerIsOnGround();

	//Function to handle the collision
	void HandlePlayerCollision();

	void ResolutionChanged();

private:

	//Menu

	C_Texture playButton;
	C_Texture editorButton;
	C_Texture settingsButton;
	C_Texture quitButton;

	//Menu_Settings
	C_Texture applyButton;
	C_Texture resolutionLabel;
	C_Texture fullHdResolution;
	C_Texture hdResolution;

	C_Texture fullscreenLabel;

	C_Texture backButton;

	TTF_Font* menuFont;
	TTF_Font* menu_SettingsFont;

	C_Texture background;

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

	static int mousePosX = 0, mousePosY = 0;
	
	SDL_GetMouseState(&mousePosX, &mousePosY);

	background.RenderTexture(0, 0);
	playButton.RenderTexture(_SCREEN_WIDTH / 2 - playButton.GetRect().w / 2 , _SCREEN_HEIGHT * 0.2 - playButton.GetRect().h /2 );
	editorButton.RenderTexture(_SCREEN_WIDTH / 2 - editorButton.GetRect().w / 2, _SCREEN_HEIGHT *0.4 - editorButton.GetRect().h / 2);
	settingsButton.RenderTexture(_SCREEN_WIDTH / 2 - settingsButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.6 - settingsButton.GetRect().h / 2 );
	quitButton.RenderTexture(_SCREEN_WIDTH / 2 - quitButton.GetRect().w / 2, _SCREEN_HEIGHT * 0.8 - quitButton.GetRect().h / 2 );

	if ( m1::IsInCollisionBox( mousePosX, mousePosY, playButton.GetRect() ) )
	{
		SDL_SetTextureAlphaMod(playButton.GetTexture(), 128);

		if (mousePressed)
		{
			return 1;
		}
		
	}

	else if (m1::IsInCollisionBox(mousePosX, mousePosY, quitButton.GetRect()))
	{
		SDL_SetTextureAlphaMod(quitButton.GetTexture(), 128);
		if (mousePressed)
		{
			return -1;
		}
	}

	else if (m1::IsInCollisionBox(mousePosX, mousePosY, editorButton.GetRect()))
	{
		SDL_SetTextureAlphaMod(editorButton.GetTexture(), 128);
		if (mousePressed)
		{
			return 2;
		}
	}

	else if (m1::IsInCollisionBox(mousePosX, mousePosY, settingsButton.GetRect()))
	{
		SDL_SetTextureAlphaMod(settingsButton.GetTexture(), 128);
		if (mousePressed)
		{
			return 3;
		}
	}

	else
	{
		SDL_SetTextureAlphaMod(playButton.GetTexture(), 255);
		SDL_SetTextureAlphaMod(quitButton.GetTexture(), 255);
		SDL_SetTextureAlphaMod(editorButton.GetTexture(), 255);
		SDL_SetTextureAlphaMod(settingsButton.GetTexture(), 255);

		return 0;
	}

}


inline bool C_Game::Game_Menu_Settings(bool mousePressed)
{

	static int mousePosX = 0, mousePosY = 0;

	SDL_GetMouseState(&mousePosX, &mousePosY);

	background.RenderTexture(0, 0);
	resolutionLabel.RenderTexture(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.15);

	applyButton.RenderTexture(_SCREEN_WIDTH - applyButton.GetRect().w, _SCREEN_HEIGHT - applyButton.GetRect().h );

	fullHdResolution.RenderTexture(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.15);

	hdResolution.RenderTexture(_SCREEN_WIDTH * 0.5, _SCREEN_HEIGHT * 0.3);

	fullscreenLabel.RenderTexture(_SCREEN_WIDTH * 0.1, _SCREEN_HEIGHT * 0.8);

	backButton.RenderTexture(0, _SCREEN_HEIGHT - backButton.GetRect().h);

	if (m1::IsInCollisionBox(mousePosX, mousePosY, applyButton.GetRect()))
	{
		SDL_SetTextureAlphaMod(applyButton.GetTexture(), 128);
		if (mousePressed)
		{
			_GetBase->SyncSettings();
			ResolutionChanged();
		}
	}

	else if (m1::IsInCollisionBox(mousePosX, mousePosY, fullHdResolution.GetRect()))
	{
		if (mousePressed)
		{
			_GetBase->SetResolution(1920, 1080);
			SDL_SetTextureAlphaMod(fullHdResolution.GetTexture(), 128);
			SDL_SetTextureAlphaMod(hdResolution.GetTexture(), 255);
		}
	}

	else if (m1::IsInCollisionBox(mousePosX, mousePosY, hdResolution.GetRect()))
	{
		if (mousePressed)
		{
			_GetBase->SetResolution(1280, 720);
			SDL_SetTextureAlphaMod(hdResolution.GetTexture(), 128);
			SDL_SetTextureAlphaMod(fullHdResolution.GetTexture(), 255);
		}
	}

	else if (m1::IsInCollisionBox(mousePosX, mousePosY, fullscreenLabel.GetRect()))
	{
		SDL_SetTextureAlphaMod(fullscreenLabel.GetTexture(), 128);

		if (mousePressed)
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
	}

	else if (m1::IsInCollisionBox(mousePosX, mousePosY, backButton.GetRect()))
	{
		SDL_SetTextureAlphaMod(backButton.GetTexture(), 128);
		if (mousePressed)
		{
			return true;
		}
	}

	else
	{
		SDL_SetTextureAlphaMod(applyButton.GetTexture(), 255);
		SDL_SetTextureAlphaMod(backButton.GetTexture(), 255);
		SDL_SetTextureAlphaMod(fullscreenLabel.GetTexture(), 255);
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

