#include "AIActionLook.h"
#include <iostream>


AIActionLook::AIActionLook(EntityAI * owner,Vector ShotLoc) : AIAction(owner)
{
	ShotLocation = ShotLoc;
}


AIActionLook::~AIActionLook()
{
}

void AIActionLook::Execute()
{
	//Get angle to look at
	Vector Delta = ShotLocation - Owner->Pos;
	float RotSpeed = 0.5;
	float Angle = 180 / 3.14 * atan2f(Delta.Y, Delta.X);
	float diff = Owner->AngleDifference(Owner->Rot, Angle);
	Owner->RotOld += copysignf(RotSpeed,diff);
	if (abs(Owner->AngleDifference(Owner->Rot, Angle)) < 5)
	{
		//std::cout << "Looked" << std::endl;
		RemoveSelf();
	}
}
AIAction * AIActionLook::CopySelf(EntityAI * newowner)
{
	AIAction * NewVer = new AIActionLook(newowner,this->ShotLocation);
	return NewVer;
}
void AIActionLook::Mutate(float Factor)
{
	Vector Delta = Vector(1, 1);
	Delta = Delta * ((rand() % 2) - 1);
	ShotLocation += Delta;
}
std::string AIActionLook::Description()
{
	return "Look at vector, " + std::to_string(ShotLocation.X) + ":" + std::to_string(ShotLocation.Y);
}