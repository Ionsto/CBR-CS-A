#include "ItemFlashBang.h"
#include <stdlib.h>
#include "EntityFlashBang.h"
#include "World.h"


ItemFlashBang::ItemFlashBang()
{
	Damage = 0;
	CoolDownTime = 200;
	ResetTime = 0;
	ResetTimer = 0;
	CoolDownTimer = 0;
	Ammo = 5;
	Inaccuracy = 0;
	Speed = 0;
	MaxDistance = 0;
}


ItemFlashBang::~ItemFlashBang()
{
}

bool ItemFlashBang::FireFrom(World * world, Vector pos, float Rot)
{
	if (CoolDownTimer < 1)
	{
		//Rot += (rand() % (int)Inaccuracy) - (Inaccuracy / 2);
		//std::cout << Inaccuracy << " Time:" << ResetTimer << " InnacTime:" << InnTime(ResetTimer) << "\n";
		EntityFlashBang * flash = new EntityFlashBang(world, pos);
		float Speed = 0.5;
		flash->PosOld -= Vector(cosf((Rot / 180) * 3.14), sinf((Rot / 180) * 3.14)) * Speed;
		world->AddEntity(flash);
		CoolDownTimer += CoolDownTime;
		ResetTimer += ResetTime;
		return true;
	}
	return false;
}