#include "Map_GameObject.h"

void Map_GameObject::save_map(const char* mapName)
{
	serialization.serialize_out(mapName, map_objects);
}

void Map_GameObject::load_map(const char* mapName)
{
	serialization.serialize_in(mapName, map_objects);
}

void Map_GameObject::new_object(unsigned short block_type, const double_Coordinate& rect)
{

	map_objects.push_back(GameObject());
	map_objects.back().init(block_type, rect);

}

void Map_GameObject::clear_map()
{
	map_objects.clear();
}