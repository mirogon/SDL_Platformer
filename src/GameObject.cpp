#include "GameObject.h"

C_GameObject::C_GameObject()
{
	if (staticTexturesInitialized == false)
	{
		InitStaticTextures();
		staticTexturesInitialized = true;
	}

	blockType = Dirt;
	position.x = 0;
	position.y = 0;

}


void C_GameObject::Init(unsigned short blockType_, double_Coordinate& pos)
{
	blockType = blockType_;
	position = pos;

}


//OPERATOR OVERLOADINGS
std::istream& operator>>(std::istream& is, C_GameObject& obj)
{
	is >> obj.position.x;
	is >> obj.position.y;

	is >> obj.blockType;

	return is;
}

std::ostream& operator<<(std::ostream& os, const C_GameObject& obj)
{

	os << obj.GetRect().x <<" ";
	os << obj.GetRect().y<<" ";

	os << obj.blockType<<" ";

	return os;
}



void C_GameObject::InitStaticTextures()
{
	textures.clear();

	textures.push_back(C_Texture());
	textures.back().Init(_DirtPath);

}

bool C_GameObject::staticTexturesInitialized = false;
std::vector<C_Texture> C_GameObject::textures;