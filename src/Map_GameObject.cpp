#include "Map_GameObject.h"

void C_Map_GameObject::SaveMap(const char* mapName)
{
	serialization.SerializeOut(mapName, mapObjects);
}

void C_Map_GameObject::LoadMap(const char* mapName)
{
	serialization.SerializeIn(mapName, mapObjects);
}

void C_Map_GameObject::NewObject(unsigned short blockType, double_Coordinate& rect)
{

	mapObjects.push_back(C_GameObject());
	mapObjects.back().Init(blockType, rect);

}

void C_Map_GameObject::ClearMap()
{
	mapObjects.clear();
}