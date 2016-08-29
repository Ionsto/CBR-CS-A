#include "ItemSMG.h"



ItemSMG::ItemSMG() : Item()
{
	Damage = 5;
	CoolDownTime = 20;
	ResetTime = 23;
	ResetTimer = 0;
	CoolDownTimer = 0;
	Ammo = 200;
	Inaccuracy = 1;
	Speed = 0;
	BaseInaccuracy = 10;
	MaxDistance = 400;
}


ItemSMG::~ItemSMG()
{
}

float ItemSMG::InnSpeed(float speed)
{
	return speed * 300;
}