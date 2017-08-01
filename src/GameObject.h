#pragma once
#include "Player.h"


class C_GameObject{
    
public:
    
	//Default GameObject constructor is invalid
    C_GameObject() = delete;

	//GameObject constructor the parameter is the blocktype which the block should be
    C_GameObject(unsigned short blockType);

	//GameObject deconstructor
    ~C_GameObject() = default;
 
	//Move the GameObject direct to x/y
    void MoveGameObjectDirect(int x, int y);
 
	//Move the GameObject +x/+y from the current position
	void MoveGameObject(float& x, float& y);
    
	//Render the GameObject at the current position
    void RenderGameObject();
    
    //Use to create the static objects
    static void CreateStaticObjects();

	//Use to delete the static objects
    static void DeleteStaticObjects();

	//Return the current GameObjectRect
	const double_Rect& GetGameObjectRect() const
	{
		return gameObjectRect;
	}

	//Return the current blocktype
    unsigned short GetBlockType(){
        return blockType;
    }
    
private:

    double_Rect gameObjectRect;
    unsigned short blockType;
    static unsigned short gameObjectCount;
    static std::vector<C_Texture> gameObjects;
    
};

inline void C_GameObject::MoveGameObjectDirect(int x, int y)
{
    gameObjectRect.x = x;
    gameObjectRect.y = y;
}

inline void C_GameObject::MoveGameObject(float& x, float& y)
{
    gameObjectRect.x += x;
    gameObjectRect.y += y;
}

inline void C_GameObject::RenderGameObject()
{

    gameObjects[blockType].RenderTexture(gameObjectRect.x, gameObjectRect.y);

}