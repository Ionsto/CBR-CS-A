#pragma once
#include "Vector.h"
#include <vector>
#include "Entity.h"
struct EntityInfo
{
	Entity::EntityType Type;
	float FlashTime;
	float Health;
	float Rot;
	Vector Position;
	bool InfoKnown;
	EntityInfo() {
	};
};
class EntityAI;
class CBREnvironment
{
public:
	//Self info
	EntityInfo Self;
	//Exterier
	EntityInfo Player;
	//Nearby simtype count
	int SameEntitiesNearby;
	EntityInfo NearbyFlashbang;
	//This would be good to have, but it turns out this is a super complex problem
	//std::vector<EntityInfo> OtherFactors;
	CBREnvironment();
	~CBREnvironment();
	void Populate(EntityAI * entity);
};

