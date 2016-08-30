#include "CBREnvironment.h"
#include "EntityWolf.h"
#include "World.h"


CBREnvironment::CBREnvironment()
{
}


CBREnvironment::~CBREnvironment()
{
}
void CBREnvironment::Populate(EntityWolf * ent)
{
	//this->Self.FlashTime = ent->FlashTime;
	this->Self.Position = ent->Pos;
	this->Self.Distance = 1000;
	this->Self.Type = ent->Type;
	//this->Player.InfoKnown = ent->RayCaster.CanSeeEntity(ent, ent->worldObj->Player);
	int SimilarEntityCloseCount = 0;
	float DistanceToClosestHerd = -1;
	EntityInfo info = EntityInfo();
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
						if (ent->worldObj->EntityList[i]->Type == Entity::EntityType::TypeHerd)
						{
							if (DistanceToClosestHerd == -1 || DistanceToClosestHerd > distsqrd)
							{
								EntityInfo info = EntityInfo();
								info.Position = ent->worldObj->EntityList[i]->Pos - this->Self.Position;
								info.Distance = sqrt(distsqrd);
								this->Herd = info;
								DistanceToClosestHerd = distsqrd;
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