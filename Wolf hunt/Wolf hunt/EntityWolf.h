#pragma once
#include <queue>
#include "EntityLiving.h"
class CBRInstance;
class CBRCase;
class AIAction;
#include "ItemRayCaster.h"
class EntityWolf :
	public EntityLiving
{
public:
	CBRInstance * AIInstance;
	CBRCase * CurrentCase;
	//Vector TargetLocation;
	int AIUpdateCounter;
	int AIUpdateMax;
	float Displacement;
	float MoveTowards;
	float MoveNormal;
	//Technicaly a normal gun, but utilises the funcitons in the item
	std::queue<AIAction *> AIStack;
	EntityWolf(World * world, Vector pos = Vector());
	~EntityWolf();
	void Update() override;
	virtual void UpdateAI();
	void ClearAIStack();
	bool CanSeeEntity(Entity * ent);
	void ActionMoveTowards(Vector midpoint);
	void ActionMoveNormal(Vector midpoint);
};

