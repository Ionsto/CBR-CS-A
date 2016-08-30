#include "EntityPlayer.h"
#include "World.h"
#include <math.h>
#include <iostream>


EntityPlayer::EntityPlayer(World * world,Vector pos) : EntityLiving(world,pos)
{
	MousePosition = Vector(0, 0);
	this->MaxForce = 25;
	this->WalkForce = 10;
	this->CurrentMaxForce = MaxForce * (Health / 100);
	this->CurrentWalkForce = WalkForce * (Health / 100);
	SetSpeed(MaxForce);
	//RotOld -= 1;
	Type = EntityType::TypePlayer;
}


EntityPlayer::~EntityPlayer()
{

}

void EntityPlayer::UpdatePlayerAngle()
{
	float RotSpeed = 0.1;
	Vector LookVector = MousePosition;
	float Angle = 180/3.14 * atan2f(LookVector.Y, LookVector.X);
	if (Rot < 170 && Angle > 170)
	{
		int i = 0;
	}
	RotOld += 0.01 * AngleDifference(Rot,Angle);
	//RotOld -= 0.1;
}
void EntityPlayer::Update()
{
	EntityLiving::Update();
	UpdatePlayerAngle();
	Vector diff = Pos - PosOld;
	this->CurrentMaxForce = MaxForce * (Health / 100);
	this->CurrentWalkForce = CurrentWalkForce * (Health / 100);
	this->CurrentMaxForce = MaxForce * (Health / 100);
}
void EntityPlayer::MoveForward()
{
	this->ApplyForce(Vector(cos((Rot / 180)*3.14) * MoveForce, sin((Rot / 180)*3.14) * MoveForce));
}
void EntityPlayer::MoveBackward()
{
	this->ApplyForce(Vector(-cos((Rot / 180)*3.14) * MoveForce, -sin((Rot / 180)*3.14) * MoveForce));
}
void EntityPlayer::MoveLeft()
{
	this->ApplyForce(Vector(cos(((Rot + 90) / 180)*3.14) * MoveForce, sin(((Rot + 90) / 180)*3.14) * MoveForce));
}
void EntityPlayer::MoveRight()
{
	this->ApplyForce(Vector(cos(((Rot - 90) / 180)*3.14) * MoveForce, sin(((Rot - 90) / 180)*3.14) * MoveForce));
}
void EntityPlayer::SetSpeed(float speed)
{
	if (MoveForce != speed)
	{
		MoveForce = speed;
	}
}