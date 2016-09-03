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
	friend std::iostream& operator<<(std::iostream& ios, const EntityInfo& einf);
	friend std::iostream& operator>>(std::iostream& ios, const EntityInfo& einf);
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
	float * SelectParam(int id);
	void Populate(EntityWolf * entity);
	friend std::iostream& operator<<(std::iostream& ios, const CBREnvironment& env);
	friend std::iostream& operator>>(std::iostream& ios, const CBREnvironment& env);
};

