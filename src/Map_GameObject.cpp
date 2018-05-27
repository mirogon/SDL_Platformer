#include "Map_GameObject.h"


void Map_GameObject::save_map(const char* map_name)
{
	serialization.serialize_out(map_name, map_objects);
}

void Map_GameObject::load_map(const char* map_name)
{
	serialization.serialize_in(map_name, map_objects);
}

void Map_GameObject::new_object(unsigned short block_type, const double_Coordinate& rect)
{

	map_objects.push_back(GameObject());
	map_objects.back().init(block_type, rect);

}

void Map_GameObject::remove_object(std::vector<GameObject>::iterator& it)
{
	map_objects.erase(it);
	map_objects.shrink_to_fit();
}

void Map_GameObject::clear_map()
{
	map_objects.clear();
}