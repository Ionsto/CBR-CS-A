#pragma once
#include "Vector.h"
#include "Entity.h"
struct HitStructure {
public:
	Vector HitPosistion;
	float HitDistance;
	HitStructure() {};
	~HitStructure() {};
};
class World;
class Item {
public:
	float Damage;
	float Speed;
	float ResetTimer;
	float CoolDownTimer;
	float ResetTime;
	float CoolDownTime;
	float Inaccuracy;
	float BaseInaccuracy;
	float MaxDistance;
	int Ammo;
	Item();
	~Item();
	virtual bool FireFrom(World * world,Vector pos,float rot);
	void ChangeSpeed(float speed);
	void DamageEntity(Entity * entity,Vector bulletpos);
	void Update(World * worldobj);
	virtual float InnSpeed(float speed);
	float InnTime(float speed);
	HitStructure * RayIntersectsEntity(Entity * entity, Vector pos, float rot);
	HitStructure * RayCasting(World * world, Vector pos, float rot);
	HitStructure * RayIntersectsWall(Vector* world, Vector pos,float rot);
};