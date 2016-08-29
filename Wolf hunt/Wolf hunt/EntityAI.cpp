#include "EntityAI.h"
#include "AIActionMove.h"
#include "AIActionLook.h"
#include "AIAction.h"
#include "CBRInstance.h"
#include "CBRCase.h"
#include "CBREnvironment.h"
#include "World.h"


EntityAI::EntityAI(World * world, Vector pos) : EntityLiving(world,pos)
{
	AIUpdateCounter = 0;
	AIUpdateMax = 100;
	AIStack = std::queue<AIAction*>();
	AIInstance = world->AIInstance;
	RayCaster = ItemRayCaster();
}


EntityAI::~EntityAI()
{
	ClearAIStack();
}

void EntityAI::ClearAIStack()
{
	while (AIStack.size() > 0)
	{
		delete AIStack.front();
		AIStack.pop();
	}
}

void EntityAI::Update()
{
	EntityLiving::Update();
	if (!Alive) { 
		return; 
	}
	if (ItemCurrent != NULL)
	{
		ItemCurrent->Update(worldObj);
	}
	//Execute the stack every frame
	if (AIStack.size() > 0) {
		AIStack.front()->Execute();
		++CurrentCase->ExecutionTime;
	}
	else
	{
		UpdateAI();
		AIUpdateCounter = AIUpdateMax;
	}
	if (AIUpdateCounter++ >= AIUpdateMax)
	{
		//UpdateAI();
		AIUpdateCounter = 0;
	}
}
void EntityAI::UpdateAI()
{
	//Get a case with the current events going on around it
	if (CurrentCase != NULL)
	{
		//Apply outcome
		CBREnvironment CurrentSituation = CBREnvironment();
		CurrentSituation.Populate(this);
		CurrentCase->CalculatedValueEnd = AIInstance->CalculateValue(CurrentSituation) + CurrentCase->ExecutionTime * 0.001;
		CurrentCase->EnviromentEnd = CurrentSituation;
		AIInstance->FeedBackCase(CurrentCase);
	}
	CBREnvironment CurrentSituation = CBREnvironment();
	CurrentSituation.Populate(this);
	this->CurrentCase = AIInstance->GetCase(CurrentSituation);
	this->CurrentCase->ApplyActionsToEntity(this);
}

bool EntityAI::CanSeeEntity(Entity * entity)
{
	if (this->FlashTime > 0)
	{
		return false;
	}
	return true;
}