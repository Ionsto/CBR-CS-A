#include "CBREnvironment.h"
#include "EntityAI.h"
#include "World.h"


CBREnvironment::CBREnvironment()
{
}


CBREnvironment::~CBREnvironment()
{
}
void CBREnvironment::Populate(EntityAI * ent)
{
	this->Self.FlashTime = ent->FlashTime;
	this->Self.Position = ent->Pos;
	this->Self.Rot = ent->Rot;
	this->Self.Type = ent->Type;
	this->Self.InfoKnown = true;
	this->Player.InfoKnown = ent->RayCaster.CanSeeEntity(ent, ent->worldObj->Player);
	if (this->Player.InfoKnown)
	{
		this->Player.FlashTime = ent->worldObj->Player->FlashTime;
		this->Player.Position = ent->worldObj->Player->Pos - this->Self.Position;
		this->Player.Rot = ent->worldObj->Player->Rot;
		this->Player.Type = ent->worldObj->Player->Type;
	}
	int SimilarEntityCloseCount = 0;
	float DistanceToClosestFlashbang = -1;
	EntityInfo info = EntityInfo();
	info.InfoKnown = false;
	this->NearbyFlashbang = info;
	for (int i = 0; i < ent->worldObj->EntityCount; ++i)
	{
		if (ent->worldObj->EntityList[i] != NULL)
		{
			if (ent != ent->worldObj->EntityList[i]) {
				if (ent->worldObj->EntityList[i]->Alive)
				{
					if (ent->RayCaster.CanSeeEntity(ent, ent->worldObj->EntityList[i]))
					{
						//Make note of it
						Vector Dist = ent->Pos - ent->worldObj->EntityList[i]->Pos;
						float distsqrd = Dist.Dot(Dist);
						if (ent->worldObj->EntityList[i]->Type == ent->Type) {
							if (distsqrd < 200)
							{
								++SimilarEntityCloseCount;
							}
						}
						if (ent->worldObj->EntityList[i]->Type == Entity::EntityType::TypeFlashbang)
						{
							if (DistanceToClosestFlashbang == -1 || DistanceToClosestFlashbang > distsqrd)
							{
								EntityInfo info = EntityInfo();
								info.Position = ent->worldObj->EntityList[i]->Pos - this->Self.Position;
								info.InfoKnown = true;
								this->NearbyFlashbang = info;
								DistanceToClosestFlashbang = distsqrd;
							}
						}
						//EntityInfo info = EntityInfo();
						//info.Position = ent->worldObj->EntityList[i]->Pos;
						//info.InfoKnown = true;
						//OtherFactors.push_back(info);
					}
				}
			}
		}
	}
}