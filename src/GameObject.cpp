#include "GameObject.h"

//std::vector<C_Texture> C_GameObject::gameObjectTextures;

C_GameObject::C_GameObject(unsigned short blockType_)
{
    if(blockType_ > gameObjectCount){
        m1::Log("Failed to create a C_GameObject with a non existant blocktype (GameObject.cpp)");
    }
    
    else
    {
        blockType = blockType_;
        gameObjectRect.x = 0;
        gameObjectRect.y = 0;
        gameObjectRect.w = gameObjects[blockType].GetRect()->w;
        gameObjectRect.h = gameObjects[blockType].GetRect()->h;
    }
}

void C_GameObject::CreateStaticObjects()
{
    
    if(alreadyCreated == false)
    {
        // Block = 0
        gameObjects.push_back(C_Texture() );
        gameObjects[0].InitTexture(_DirtPath);
        ++gameObjectCount;
        
		alreadyCreated = true;
    }
    
}

void C_GameObject::DeleteStaticObjects()
{
	gameObjects.clear();
	alreadyCreated = false;
	gameObjectCount = 0;
}

unsigned short C_GameObject::gameObjectCount = 0;
std::vector<C_Texture> C_GameObject::gameObjects;
bool C_GameObject::alreadyCreated = false;