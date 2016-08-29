#include "EntityFlashBang.h"
#include "World.h"
#include "ItemBlinder.h"


EntityFlashBang::EntityFlashBang(World * world,Vector pos) : EntityLiving(world,pos)
{
	SetSize(0.1);
	Mass = 50;
	Friction = 0.998;
	FlightTimeCurrent = 0;
	FlightTimeMax = 500;
	ItemList[0] = new ItemBlinder();
	ItemCurrent = ItemList[0];
	Elasticity = 1;
	Type = EntityType::TypeFlashbang;
}


EntityFlashBang::~EntityFlashBang()
{
}

void EntityFlashBang::Update()
{
	EntityLiving::Update();
	if (!Alive) { return; }
	if (FlightTimeCurrent++ > FlightTimeMax)
	{
		//Detonate
		this->Detonate();
	}
}
void EntityFlashBang::Detonate()
{
	//for each entity attempt to blind them
	for (int i = 0; i < worldObj->EntityCount;++i)
	{
		if (worldObj->EntityList[i] != NULL)
		{
			if (worldObj->EntityList[i]->Alive)
			{
				if (worldObj->EntityList[i]->Type != EntityType::TypeEntity && worldObj->EntityList[i]->Type != EntityType::TypeFlashbang)
				{
					//Attempt to flash it
					Vector dist = worldObj->EntityList[i]->Pos - Pos;
					float Angle = 180 / 3.14 * atan2f(dist.Y, dist.X);
					float GunSize = Size * 1.5;
					Vector FireFrom = Pos + Vector(GunSize * cosf(Angle / 180 * 3.14), GunSize * sinf(Angle / 180 * 3.14));
					(ItemCurrent)->FireFrom(worldObj, FireFrom, Angle);
				}
			}
		}
	}
	Kill();
}