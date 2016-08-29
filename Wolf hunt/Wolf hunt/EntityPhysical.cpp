#include "EntityPhysical.h"
#include "World.h"
#include "GameManager.h"

EntityPhysical::EntityPhysical(World * world) : Entity(world)
{
}
EntityPhysical::~EntityPhysical()
{
}
void EntityPhysical::Update()
{
 	UpdatePhysics();
}
void EntityPhysical::UpdatePhysics()
{
	X = PhyObject->GetPosition().x;
	Y = PhyObject->GetPosition().y;
	R = PhyObject->GetAngle();
}