#include "GameObject.h"

C_Object C_GameObject::object;

//OPERATOR OVERLOADINGS
std::istream& operator>>(std::istream& is, C_GameObject& obj)
{
	static double_Rect cache;

	is >> cache.x;
	is >> cache.y;
	is >> cache.w;
	is >> cache.h;

	obj.MoveGameObjectDirect(cache);

	return is;
}

std::ostream& operator<<(std::ostream& os, const C_GameObject& obj)
{

	os << obj.GetGameObjectRect().x;
	os << obj.GetGameObjectRect().y;
	os << obj.GetGameObjectRect().w;
	os << obj.GetGameObjectRect().h;

	return os;
}