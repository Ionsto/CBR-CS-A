#include "ItemBlinder.h"
#include <stdlib.h>
#include "EntityTracerEffect.h"
#include "World.h"


ItemBlinder::ItemBlinder()
{
}


ItemBlinder::~ItemBlinder()
{
}

HitStructure * ItemBlinder::RayCasting(World * world, Vector pos, float Rot)
{
	Entity * HitEntity = NULL;
	HitStructure * LesserHitData = NULL;
	for (int i = 0; i < world->EntityCount; ++i)
	{
		if (world->EntityList[i] != NULL)
		{
			HitStructure * hitData = RayIntersectsEntity(world->EntityList[i], pos, Rot);
			if (hitData != NULL)
			{
				if (LesserHitData == NULL)
				{
					LesserHitData = hitData;
					HitEntity = world->EntityList[i];
				}
				else
				{
					if (hitData->HitDistance < LesserHitData->HitDistance) {
						HitEntity = world->EntityList[i];
						LesserHitData = hitData;
					}

				}
			}
		}
	}
	for (int i = 0; i < world->WorldCollision.size(); ++i)
	{
		HitStructure * hitData = RayIntersectsWall(world->WorldCollision.at(i), pos, Rot);
		if (hitData != NULL)
		{
			if (LesserHitData == NULL)
			{
				LesserHitData = hitData;
			}
			else
			{
				if (hitData->HitDistance < LesserHitData->HitDistance) {
					HitEntity = NULL;
					LesserHitData = hitData;
				}

			}
		}
	}
	if (HitEntity != NULL) {
		if (dynamic_cast<EntityLiving*>(HitEntity) != NULL) {
			((EntityLiving*)HitEntity)->Flash(pos);
		}
		//this->DamageEntity(HitEntity, LesserHitData->HitPosistion);
	}
	return LesserHitData;
}

bool ItemBlinder::FireFrom(World * world, Vector pos, float Rot)
{
	//std::cout << Inaccuracy <<" Time:"<< ResetTimer << " InnacTime:"<< InnTime(ResetTimer)<< "\n";
	HitStructure * hitpos = RayCasting(world, pos, Rot);
	if (hitpos == NULL) {
		hitpos = new HitStructure();
		hitpos->HitDistance = MaxDistance;
		hitpos->HitPosistion = Vector((MaxDistance * cosf(Rot / 180 * 3.14)) + pos.X, (MaxDistance * sinf(Rot / 180 * 3.14)) + pos.Y);
	}
	//world->AddEntity(new EntityTracerEffect(world, pos, hitpos->HitPosistion));
	delete hitpos;
	Ammo -= 1;
	CoolDownTimer += CoolDownTime;
	ResetTimer += ResetTime;
	return true;
	return false;
}