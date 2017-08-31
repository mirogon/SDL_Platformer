#pragma once
#include "Player.h"


class C_GameObject{
    
public:
    
	//Default GameObject constructor is invalid
	C_GameObject() = default;

	//GameObject deconstructor
    virtual ~C_GameObject() = default;
 
	virtual void Init() = 0;

	//Move the GameObject direct to x/y
    void MoveGameObjectDirect(int x, int y);
 
	//Move the GameObject +x/+y from the current position
	void MoveGameObject(float& x, float& y);
    
	//Render the GameObject at the current position
    void RenderGameObject();
    
	void PrintGameObjectStats()
	{
		m1::Log("Gameobject Stats:");
		m1::Log("x" + m1::to_string(object.GetObjectRect().x));
		m1::Log("y" + m1::to_string(object.GetObjectRect().y));
		m1::Log("w" + m1::to_string(object.GetObjectRect().w));
		m1::Log("h" + m1::to_string(object.GetObjectRect().h));
	}

	//Return the current GameObjectRect
	const double_Rect& GetGameObjectRect() const
	{
		return object.GetObjectRect();
	}
    
protected:

	//Static member
    static C_Object object;
    
};

inline void C_GameObject::MoveGameObjectDirect(int x, int y)
{
    object.MoveObjectDirect(x, y);
}

inline void C_GameObject::MoveGameObject(float& x, float& y)
{
	object.MoveObject(x, y);
}

inline void C_GameObject::RenderGameObject()
{
	object.RenderObject();
}