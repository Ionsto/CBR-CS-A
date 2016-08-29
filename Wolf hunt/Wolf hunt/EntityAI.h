#pragma once
#include <queue>
#include "EntityLiving.h"
class CBRInstance;
class CBRCase;
class AIAction;
#include "ItemRayCaster.h"
class EntityAI :
	public EntityLiving
{
public:
	CBRInstance * AIInstance;
	CBRCase * CurrentCase;
	int AIUpdateCounter;
	int AIUpdateMax;
	//Technicaly a normal gun, but utilises the funcitons in the item
	ItemRayCaster RayCaster;
	std::queue<AIAction *> AIStack;
	EntityAI(World * world, Vector pos = Vector());
	~EntityAI();
	void Update() override;
	virtual void UpdateAI();
	void ClearAIStack();
	bool CanSeeEntity(Entity * ent);
};

