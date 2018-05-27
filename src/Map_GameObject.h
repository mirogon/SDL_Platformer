#pragma once
#include "GameObject.h"

class Map_GameObject
{
public:

	Map_GameObject() = default;
	~Map_GameObject() = default;

	void save_map(const char* mapName);
	void load_map(const char* mapName);

	void new_object(unsigned short block_type, const double_Coordinate& rect);
	void remove_object(std::vector<GameObject>::iterator& it);

	void render_map();

	void clear_map();

	std::vector<GameObject>& get_map_objects()
	{
		return map_objects;
	}

private:

	std::vector<GameObject> map_objects;
	m1::S_Serialization<GameObject> serialization;
};

inline void Map_GameObject::render_map()
{
	for (auto i = map_objects.begin(); i != map_objects.end(); ++i)
	{
		i->render();
	}
}