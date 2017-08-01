#include "Game.h"

C_Game::C_Game()
{
	gameObjects.push_back(C_GameObject(0));
	player.MoveObjectDirect(SCREEN_WIDTH / 2 - player.GetObjectRect().w / 2, SCREEN_HEIGHT - player.GetObjectRect().h);
	gameObjects[0].MoveGameObjectDirect(SCREEN_WIDTH / 2 - gameObjects[0].GetGameObjectRect().w / 2, SCREEN_HEIGHT - 100 );
	playerIsOnGameObject = false;
	background.InitTexture(_BackgroundPath);
	
}

C_Game::~C_Game()
{

	std::vector<C_GameObject>().swap(gameObjects);

}
