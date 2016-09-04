#pragma once
#include "Vector.h"
#include <vector>
#include "Entity.h"
struct EntityInfo
{
	int Type;
	Vector Position;
	float Distance;
	EntityInfo() {
	};
	friend std::ostream& operator<<(std::ostream& ios, const EntityInfo& einf);
	friend std::istream& operator>>(std::istream& ios, EntityInfo& einf);
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
	float& GetInputParams(int id);
	void Populate(EntityWolf * entity);
	friend std::ostream& operator<<(std::ostream& ios, const CBREnvironment& env);
	friend std::istream& operator>>(std::istream& ios, CBREnvironment& env);
};

