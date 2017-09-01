#pragma once
#include "Player.h"


class C_GameObject
{
	
	friend std::istream& operator>>(std::istream& is, C_GameObject& obj);
	friend std::ostream& operator<<(std::ostream& os, const C_GameObject& obj);

public:
    
	//Default GameObject constructor is invalid
	C_GameObject();

	//GameObject deconstructor
    virtual ~C_GameObject() = default;
 
	virtual void Init(unsigned short blockType_, double_Coordinate& pos);

	//Move the GameObject direct to x/y
    virtual void MoveDirect(int x, int y);

	virtual void MoveDirect(const double_Coordinate& newPos);
 
	//Move the GameObject +x/+y from the current position
	virtual void Move(float& x, float& y);
    
	//Render the GameObject at the current position
    virtual void Render();
    
	void PrintGameObjectStats()
	{
		m1::Log("Gameobject Stats:");
		m1::Log("x" + m1::to_string(position.x));
		m1::Log("y" + m1::to_string(position.y));
		m1::Log("w" + m1::to_string(textures.at(blockType).GetRect().w));
		m1::Log("h" + m1::to_string(textures.at(blockType).GetRect().h));
	}

	//Return the current GameObjectRect
	virtual const double_Rect& GetRect() const
	{
		static double_Rect r;
		r.x = position.x;
		r.y = position.y;
		r.w = textures.at(blockType).GetRect().w;
		r.h = textures.at(blockType).GetRect().h;
		
		return r;
	}

	static void InitStaticTextures();

private:

	static bool staticTexturesInitialized;
	

	unsigned short blockType;
	double_Coordinate position;

	//Static member
    static std::vector<C_Texture> textures;
    
};



inline void C_GameObject::MoveDirect(int x, int y)
{
	position.x = x;
	position.y = y;
}

inline void C_GameObject::MoveDirect(const double_Coordinate& newPos)
{
	position = newPos;
}

inline void C_GameObject::Move(float& x, float& y)
{
	position.x += x;
	position.y += y;
}

inline void C_GameObject::Render()
{
	textures.at(blockType).RenderTexture(position.x, position.y);
}