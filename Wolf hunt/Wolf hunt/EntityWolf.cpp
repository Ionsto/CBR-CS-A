#include "EntityWolf.h"
#include "AIActionMove.h"
#include "AIAction.h"
#include "CBRInstance.h"
#include "CBRCase.h"
#include "CBREnvironment.h"
#include "World.h"


EntityWolf::EntityWolf(World * world, Vector pos) : EntityLiving(world,pos)
{
	AIUpdateCounter = 0;
	AIUpdateMax = 1000;
	AIStack = std::queue<AIAction*>();
	AIInstance = world->AIInstance;
	TargetLocation = pos;
	Displacement = 0;
}


EntityWolf::~EntityWolf()
{
	ClearAIStack();
}

void EntityWolf::ClearAIStack()
{
	while (AIStack.size() > 0)
	{
		delete AIStack.front();
		AIStack.pop();
	}
}

void EntityWolf::Update()
{
	Vector Diff = Pos - PosOld;
	Displacement += Diff.Dot(Diff);
	EntityLiving::Update();
	if (!Alive) { 
		return; 
	}
	//Execute the stack every frame
	/*if (AIStack.size() > 0) {
		AIStack.front()->Execute();
		++CurrentCase->ExecutionTime;
	}
	else
	{
		UpdateAI();
		AIUpdateCounter = AIUpdateMax;
	}*/
	Vector Distance = TargetLocation - Pos;
	float DistanceSqrd = Distance.Dot(Distance);
	if (DistanceSqrd > 10) {
		Distance = Distance / sqrtf(DistanceSqrd);
		ApplyForce(Distance * MoveForce);
	}
	else
	{
		UpdateAI();
		//AIUpdateCounter = AIUpdateMax;
	}
	if (AIUpdateCounter++ >= AIUpdateMax)
	{
		if (Displacement < 2) 
		{
			UpdateAI();
			Displacement = 0;
		}	
		AIUpdateCounter = 0;
	}
}
void EntityWolf::UpdateAI()
{
	//Get a case with the current events going on around it
	if (CurrentCase != NULL)
	{
		//Apply outcome
		CBREnvironment CurrentSituation = CBREnvironment();
		CurrentSituation.Populate(this);
		CurrentCase->CalculatedValueEnd = AIInstance->CalculateValue(CurrentSituation);
		CurrentCase->DeltaValue = CurrentCase->CalculatedValueEnd - CurrentCase->CalculatedValueStart;
		CurrentCase->EnviromentEnd = CurrentSituation;
		AIInstance->FeedBackCase(CurrentCase);
	}
	CBREnvironment CurrentSituation = CBREnvironment();
	CurrentSituation.Populate(this);
	this->CurrentCase = AIInstance->GetCase(CurrentSituation);
	this->CurrentCase->ApplyActionsToEntity(this);
}

bool EntityWolf::CanSeeEntity(Entity * entity)
{
	return true;
}