#include "Item.h"
#include "World.h"
#include "Entity.h"
#include <math.h>
#include <iostream>
Item::Item()
{
	Damage = 10;
	CoolDownTime = 70;
	ResetTime = 90;
	ResetTimer = 0;
	CoolDownTimer = 0;
	Ammo = 100;
	Inaccuracy = 1;
	Speed = 0;
	BaseInaccuracy = 4;
	MaxDistance = 500;
}
Item::~Item()
{

}
//Negitive values show nonhit
HitStructure * Item::RayIntersectsWall(Vector * WorldCollision, Vector Pos,float rot)
{
	Vector LesserPos = WorldCollision[0];
	Vector GreaterPos = WorldCollision[0] + WorldCollision[1];
	Vector RayComp = Vector(1/cosf((rot / 180) * 3.14), 1/sinf((rot / 180) * 3.14));
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t;
	float t1 = (LesserPos.X - Pos.X)*RayComp.X;
	float t2 = (GreaterPos.X - Pos.X)*RayComp.X;
	float t3 = (LesserPos.Y - Pos.Y)*RayComp.Y;
	float t4 = (GreaterPos.Y - Pos.Y)*RayComp.Y;

	float tmin = fmaxf(fminf(t1, t2), fminf(t3, t4));
	float tmax = fminf(fmaxf(t1, t2), fmaxf(t3, t4));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0)
	{
		return NULL;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return NULL;
	}
	HitStructure * hitPos = new HitStructure();
	hitPos->HitDistance = tmin;
	hitPos->HitPosistion = Pos + Vector(tmin * cosf((rot / 180) * 3.14), tmin * sinf((rot / 180) * 3.14));
	return hitPos;
	return NULL;
}
bool Item::FireFrom(World * world, Vector pos, float Rot)
{
	if (Ammo > 0)
	{
		if (CoolDownTimer < 1)
		{
			Rot += (rand() % (int)Inaccuracy) - (Inaccuracy/2);
			//std::cout << Inaccuracy <<" Time:"<< ResetTimer << " InnacTime:"<< InnTime(ResetTimer)<< "\n";
			HitStructure * hitpos = RayCasting(world, pos, Rot);
			if (hitpos == NULL) {
				hitpos = new HitStructure();
				hitpos->HitDistance = MaxDistance;
				hitpos->HitPosistion = Vector((MaxDistance * cosf(Rot / 180 * 3.14)) + pos.X , (MaxDistance * sinf(Rot / 180 * 3.14)) + pos.Y);
			}
			//world->AddEntity(new EntityTracerEffect(world, pos, hitpos->HitPosistion));
			delete hitpos;
			Ammo -= 1;
			CoolDownTimer += CoolDownTime;
			ResetTimer += ResetTime;
			return true;
		}
	}
	return false;
}
void Item::Update(World * worldObj)
{
	ResetTimer -= 1 * worldObj->DeltaTime;
	CoolDownTimer -= 1 * worldObj->DeltaTime;
	if (ResetTimer > 300)
	{
		ResetTimer = 300;
	}
	if (ResetTimer < 0)
	{
		ResetTimer = 0;
	}
	if (CoolDownTimer < 0)
	{
		CoolDownTimer = 0;
	}
	Inaccuracy = BaseInaccuracy + InnSpeed(Speed) + InnTime(ResetTimer);
	Inaccuracy = fminf(90, Inaccuracy);
}
float Item::InnSpeed(float speed)
{
	return speed * 1000;
}
float Item::InnTime(float time)
{
	return 0.5*time;
}
HitStructure * Item::RayIntersectsEntity(Entity * entity, Vector pos, float rot)
{
	Vector RayComp = Vector(cosf((rot / 180) * 3.14), sinf((rot / 180) * 3.14));
	Vector Ray = RayComp * MaxDistance;
	Vector AC = entity->Pos - pos;
	float DDistance = AC.Dot(Ray) / MaxDistance;
	if (DDistance >= 0) {
		Vector DPos = RayComp * DDistance;
		Vector Distance = DPos - AC;
		float DistanceSquared = Distance.Dot(Distance);
		if (DistanceSquared < entity->Size * entity->Size)
		{
			//Within circle
			float NewDistance = DDistance -sqrtf((entity->Size * entity->Size) - DistanceSquared);
			if (NewDistance <= MaxDistance) {
				HitStructure * hit = new HitStructure();
				hit->HitDistance = NewDistance;
				hit->HitPosistion = Vector((RayComp.X * NewDistance) + pos.X, (RayComp.Y * NewDistance) + pos.Y);
				return hit;
			}
		}
	}
	return NULL;
}
HitStructure * Item::RayCasting(World * world, Vector pos, float Rot)
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
						delete LesserHitData;
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
					delete LesserHitData;
					LesserHitData = hitData;
				}

			}
		}
	}
	if (HitEntity != NULL) {
		this->DamageEntity(HitEntity, LesserHitData->HitPosistion);
	}
	return LesserHitData;
}
void Item::ChangeSpeed(float speed)
{
	Speed = speed;
}
void Item::DamageEntity(Entity * entity, Vector pos)
{
	entity->DoDamage(Damage);
	entity->Acc += (entity->Pos - pos) * 5;
}