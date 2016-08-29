#include "EntityFlashTurret.h"
#include "AIActionShoot.h"
#include "ItemFlashBang.h"
#include "World.h"


EntityFlashTurret::EntityFlashTurret(World * world,Vector pos) : EntityAI(world,pos)
{
	this->ItemList[3] = new ItemFlashBang();
	this->AIUpdateCounter = AIUpdateMax;
	this->AIStack.push(new AIActionShoot(this, 3, 1000));
}


EntityFlashTurret::~EntityFlashTurret()
{
}

void EntityFlashTurret::UpdateAI()
{
}