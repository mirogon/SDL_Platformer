#pragma once
#include "GameObject.h"

//Enum to check the collision direction
enum E_CollisionDirection { Left = 0, Right = 1, Bot = 2, Top = 3 };

E_CollisionDirection CollisionDetection( const double_Rect& pCollisionBox, const double_Rect& collisionBox);

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
 
	void PlayerInBorders();

	//Check and return if the player is on the ground
	bool PlayerIsOnGround();

	//Function to handle the collision
	void HandlePlayerCollision();

private:

	C_Texture playButton;
	C_Texture editorButton;
	C_Texture quitButton;

	//The background texture
	C_Texture background;

	//The player
    C_Player player;

	//The game objects
    std::vector<C_GameObject> gameObjects;

	bool playerIsOnGameObject;
    
};

inline void C_Game::Game_Play()
{
    static Uint32 lastTime = SDL_GetTicks();
    
    if(m1::KeyIsPressed(SDL_SCANCODE_SPACE) && PlayerIsOnGround())
    {
        player.Jump();
    }
    
    player.Fall(SDL_GetTicks() - lastTime);

	player.PlayerWalk();

	PlayerInBorders();

	HandlePlayerCollision();
    
	background.RenderTexture(0, 0);

    player.RenderObject();
    
    gameObjects[0].RenderGameObject();

    lastTime = SDL_GetTicks();

}

inline short C_Game::Game_Menu(bool mousePressed)
{

	static int mousePosX = 0, mousePosY = 0;
	
	SDL_GetMouseState(&mousePosX, &mousePosY);

	playButton.RenderTexture(SCREEN_WIDTH / 2 - playButton.GetRect()->w / 2 , SCREEN_HEIGHT * 0.25 - playButton.GetRect()->h );
	editorButton.RenderTexture(SCREEN_WIDTH / 2 - editorButton.GetRect()->w / 2, SCREEN_HEIGHT / 2 - editorButton.GetRect()->h / 2);
	quitButton.RenderTexture(SCREEN_WIDTH / 2 - quitButton.GetRect()->w / 2, SCREEN_HEIGHT * 0.75);

	if ( m1::IsInCollisionBox( mousePosX, mousePosY, *playButton.GetRect() ) )
	{
		SDL_SetTextureAlphaMod(playButton.GetTexture(), 128);

		if (mousePressed)
		{
			return 1;
		}
		
	}

	else if (m1::IsInCollisionBox(mousePosX, mousePosY, *quitButton.GetRect()))
	{
		SDL_SetTextureAlphaMod(quitButton.GetTexture(), 128);
		if (mousePressed)
		{
			return -1;
		}
	}

	else
	{
		SDL_SetTextureAlphaMod(playButton.GetTexture(), 255);
		SDL_SetTextureAlphaMod(quitButton.GetTexture(), 255);
		return 0;
	}

}


inline bool C_Game::PlayerIsOnGround()
{
    if(player.GetObjectRect().y + player.GetObjectRect().h >= SCREEN_HEIGHT || playerIsOnGameObject == true)
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
	if (player.GetObjectRect().x < 0) 
	{
		player.MoveObjectDirect(0, player.GetObjectRect().y);
	}

	else if (player.GetObjectRect().x > SCREEN_WIDTH - player.GetObjectRect().w)
	{
		player.MoveObjectDirect(SCREEN_WIDTH - player.GetObjectRect().w, player.GetObjectRect().y);
	}

	if (player.GetObjectRect().y < 0)
	{
		player.MoveObjectDirect(player.GetObjectRect().x, 0);
	}

	else if (player.GetObjectRect().y > SCREEN_HEIGHT - player.GetObjectRect().h)
	{
		player.MoveObjectDirect(player.GetObjectRect().x, SCREEN_HEIGHT - player.GetObjectRect().h);
	}


}

inline void C_Game::HandlePlayerCollision()
{
	for (auto iT = gameObjects.begin(); iT != gameObjects.end(); ++iT)
	{

		switch (CollisionDetection(player.GetObjectRect(), iT->GetGameObjectRect()))
		{

			case Bot:	player.ResetVelocity();
						player.MoveObjectDirect(player.GetObjectRect().x, iT->GetGameObjectRect().y + iT->GetGameObjectRect().h + 1);
						playerIsOnGameObject = false;
						break;

			case Top:	player.MoveObjectDirect(player.GetObjectRect().x, iT->GetGameObjectRect().y - player.GetObjectRect().h);
						playerIsOnGameObject = true;
						break;

			case Left:	player.MoveObjectDirect(iT->GetGameObjectRect().x - player.GetObjectRect().w, player.GetObjectRect().y);
						playerIsOnGameObject = false;
						break;

			case Right: player.MoveObjectDirect(iT->GetGameObjectRect().x + iT->GetGameObjectRect().w, player.GetObjectRect().y);
						playerIsOnGameObject = false;
						break;

			default:	playerIsOnGameObject = false;

		}

	}

}

inline E_CollisionDirection CollisionDetection(const double_Rect& pCollisionBox, const double_Rect& collisionBox)
{
	float w = 0.5 * (pCollisionBox.w + collisionBox.w);
	float h = 0.5 * (pCollisionBox.h + collisionBox.h);
	float dx = double_Rect::GetCenterX(pCollisionBox) - double_Rect::GetCenterX(collisionBox);
	float dy = double_Rect::GetCenterY(pCollisionBox) - double_Rect::GetCenterY(collisionBox);

	if (abs(dx) <= w && abs(dy) <= h)
	{
		/* collision! */
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				return Bot;
			}

			else
			{
				return Left;
			}
		}

		else
		{
			if (wy > -hx)
			{
				return Right;
			}

			else
			{
				return Top;
			}

		}

	}

}

