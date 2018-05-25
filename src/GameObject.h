#pragma once
#include "Player.h"


class GameObject
{
	
	friend std::istream& operator>>(std::istream& is, GameObject& obj);
	friend std::ostream& operator<<(std::ostream& os, const GameObject& obj);

public:
    
	//Default GameObject constructor is invalid
	GameObject(short block_type = 0);

	//GameObject deconstructor
    virtual ~GameObject() = default;
 
	virtual void init(unsigned short block_type_, const double_Coordinate& pos);

	//move the GameObject direct to x/y
    virtual void move_direct(int x, int y);

	virtual void move_direct(const double_Coordinate& new_pos);
 
	//move the GameObject +x/+y from the current position
	virtual void move(float& x, float& y);
    
	//render the GameObject at the current position
    virtual void render();
    
	short get_block_type() const
	{
		return block_type;
	}

	void print_gameobject_info()
	{
		m1::log("Gameobject Stats:");
		m1::log("x" + m1::to_string(position.x));
		m1::log("y" + m1::to_string(position.y));
		m1::log("w" + m1::to_string(textures.at(block_type).get_rect().w));
		m1::log("h" + m1::to_string(textures.at(block_type).get_rect().h));
	}

	//Return the current GameObjectRect
	virtual const double_Rect& get_rect() const
	{
		static double_Rect r;
		r.x = position.x;
		r.y = position.y;
		r.w = textures.at(block_type).get_rect().w;
		r.h = textures.at(block_type).get_rect().h;
		
		return r;
	}

	static void init_static_textures();

private:

	static bool static_textures_initialized;
	

	short block_type;
	double_Coordinate position;

	//Static member
    static std::vector<Texture> textures;
    
};



inline void GameObject::move_direct(int x, int y)
{
	position.x = x;
	position.y = y;
}

inline void GameObject::move_direct(const double_Coordinate& new_pos)
{
	position = new_pos;
}

inline void GameObject::move(float& x, float& y)
{
	position.x += x;
	position.y += y;
}

inline void GameObject::render()
{
	textures.at(block_type).render_texture(position.x, position.y);
}