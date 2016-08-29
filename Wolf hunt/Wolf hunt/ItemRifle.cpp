#include "ItemRifle.h"



ItemRifle::ItemRifle() : Item()
{
	Damage = 10;
	CoolDownTime = 70;
	ResetTime = 80;
	ResetTimer = 0;
	CoolDownTimer = 0;
	Ammo = 100;
	Inaccuracy = 1;
	Speed = 0;
	MaxDistance = 500;
}


ItemRifle::~ItemRifle()
{

}
