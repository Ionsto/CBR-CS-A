#pragma once
#include "Vector.h"
#include <vector>
#include "Entity.h"
struct EntityInfo
{
	Entity::EntityType Type;
	Vector Position;
	float Distance;
	EntityInfo() {
	};
};
class EntityWolf;
class CBREnvironment
{
public:
	//Self info
	EntityInfo Self;
	//Exterier
	EntityInfo Herd;
	//Nearby simtype count
	int HerdCount;
	//This would be good to have, but it turns out this is a super complex problem
	//std::vector<EntityInfo> OtherFactors;
	CBREnvironment();
	~CBREnvironment();
	void Populate(EntityWolf * entity);
};

