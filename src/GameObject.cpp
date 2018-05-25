#include "GameObject.h"

GameObject::GameObject(short block_type_)
{
	if (static_textures_initialized == false)
	{
		init_static_textures();
		static_textures_initialized = true;
	}

	block_type = block_type_;
	position.x = 0;
	position.y = 0;

}


void GameObject::init(unsigned short block_type_, const double_Coordinate& pos)
{
	block_type = block_type_;
	position = pos;

}


//OPERATOR OVERLOADINGS
std::istream& operator>>(std::istream& is, GameObject& obj)
{
	is >> obj.position.x;
	is >> obj.position.y;

	is >> obj.block_type;

	return is;
}

std::ostream& operator<<(std::ostream& os, const GameObject& obj)
{

	os << obj.get_rect().x <<" ";
	os << obj.get_rect().y<<" ";

	os << obj.block_type<<" ";

	return os;
}



void GameObject::init_static_textures()
{
	textures.clear();

	textures.push_back(Texture());
	textures.back().init(_PATH_DIRT);

}

bool GameObject::static_textures_initialized = false;
std::vector<Texture> GameObject::textures;