#pragma once
#include "GameObject.h"

class C_Map_GameObject
{
public:

	C_Map_GameObject() = default;
	~C_Map_GameObject() = default;

	void SaveMap(const char* mapName);
	void LoadMap(const char* mapName);

	void NewObject(unsigned short blockType, double_Coordinate& rect);

	void RenderMap();

	void ClearMap();

	std::vector<C_GameObject>& GetMapObjects()
	{
		return mapObjects;
	}

private:

	std::vector<C_GameObject> mapObjects;
	m1::S_Serialization<C_GameObject> serialization;
};

inline void C_Map_GameObject::RenderMap()
{
	for (auto i = mapObjects.begin(); i != mapObjects.end(); ++i)
	{
		i->Render();
	}
}