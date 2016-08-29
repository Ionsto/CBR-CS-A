#pragma once
#include "EntityLiving.h"
class EntityFlashBang :
	public EntityLiving
{
public:
	float FlightTimeCurrent;
	float FlightTimeMax;
	EntityFlashBang(World * world, Vector pos = Vector());
	~EntityFlashBang();
	void Update() override;
	void Detonate();
};

