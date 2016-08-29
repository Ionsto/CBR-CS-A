#include "ItemRayCaster.h"
#include "Entity.h"
#include "World.h"
#include <math.h>


ItemRayCaster::ItemRayCaster()
{
	MaxDistance = 1000;
}


ItemRayCaster::~ItemRayCaster()
{
}

bool ItemRayCaster::CanSeeEntity(Entity * me, Entity * them)
{
	Vector Distance = them->Pos - me->Pos;
	float Rot = 180 / 3.14 * atan2f(Distance.Y, Distance.X);

	Entity * HitEntity = NULL;
	HitStructure * LesserHitData = NULL;
	for (int i = 0; i < me->worldObj->EntityCount; ++i)
	{
		if (me->worldObj->EntityList[i] != NULL)
		{
			if (me->worldObj->EntityList[i] != me) {
				HitStructure * hitData = RayIntersectsEntity(me->worldObj->EntityList[i], me->Pos, Rot);
				if (hitData != NULL)
				{
					if (LesserHitData == NULL)
					{
						LesserHitData = hitData;
						HitEntity = me->worldObj->EntityList[i];
					}
					else
					{
						if (hitData->HitDistance < LesserHitData->HitDistance) {
							HitEntity = me->worldObj->EntityList[i];
							delete LesserHitData;
							LesserHitData = hitData;
						}

					}
				}
			}
		}
	}
	for (int i = 0; i < me->worldObj->WorldCollision.size(); ++i)
	{
		HitStructure * hitData = RayIntersectsWall(me->worldObj->WorldCollision.at(i), me->Pos, Rot);
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
	delete LesserHitData;
	if (HitEntity != NULL) {
		return true;
	}
	return false;
}
float ItemRayCaster::Distance(Vector pos, float Rot)
{
	return 0;
}