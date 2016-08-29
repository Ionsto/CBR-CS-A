#include "EntityPlayer.h"
#include "World.h"
#include <math.h>
#include <iostream>
#include "ItemSword.h"
#include "ItemRifle.h"
#include "ItemSMG.h"
#include "ItemFlashBang.h"


EntityPlayer::EntityPlayer(World * world,Vector pos) : EntityLiving(world,pos)
{
	MousePosition = Vector(0, 0);
	ItemList[0] = new ItemSword();
	ItemList[1] = new ItemRifle();
	ItemList[2] = new ItemSMG();
	ItemList[3] = new ItemFlashBang();
	ItemCurrent = ItemList[0];
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
	ItemCurrent->Update(worldObj);
	Vector diff = Pos - PosOld;
	ItemCurrent->ChangeSpeed(diff.Dot(diff));
	this->CurrentMaxForce = MaxForce * (Health / 100);
	this->CurrentWalkForce = CurrentWalkForce * (Health / 100);
	this->CurrentMaxForce = MaxForce * (Health / 100);
}
void EntityPlayer::ChangeItemCurrent(int number)
{
	if (number < 4) {
		ItemCurrent = ItemList[number];
	}
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
void EntityPlayer::Flash(Vector Position)
{
	Vector dist = Position - Pos;
	float Angle = 180 / 3.14 * atan2f(dist.Y, dist.X);
	FlashTime = worldObj->FlashManager->MaxFlashTime * (1 - (abs(AngleDifference(Rot,Angle))/90));
	if (FlashTime < 2)
	{
		FlashTime = 2;
	}
	//Make entire screen white
	worldObj->FlashManager->AddFlashBangEvent(this,Position);
}