#include "AIActionMove.h"
#include <math.h>


AIActionMove::AIActionMove(EntityWolf * owner, Vector pos) : AIAction(owner)
{
	Position = pos;
	EvalCount = 0;
	EvalTime = 200;
	OldPosition = Vector(-FP_INFINITE,-FP_INFINITE);
}


AIActionMove::~AIActionMove()
{
}

void AIActionMove::Execute()
{
	//Calculate 
	Vector Distance = Position - Owner->Pos;
	float DistanceSqrd = Distance.Dot(Distance);
	if (DistanceSqrd > 10) {
		Distance = Distance / sqrtf(DistanceSqrd);
		Owner->ApplyForce(Distance * Owner->MoveForce);
		//Owner->Acc;
		if (EvalCount++ >= EvalTime)
		{
			EvalCount = 0;
			//Evaluate if we are actualy moving at all
			Vector Distance = OldPosition - Owner->Pos;
			if (Distance.Dot(Distance) < 1) {
				//We are not moving, so self terminate
				RemoveSelf();
				return;
			}
			OldPosition = Owner->Pos;
		}
	}
	else
	{
		//Remove from AI stack
		RemoveSelf();
	}
}
AIAction * AIActionMove::CopySelf(EntityWolf * newowner)
{
	AIAction * NewVer = new AIActionMove(newowner, this->Position);
	return NewVer;
}
void AIActionMove::Mutate(float Factor)
{
	Vector Delta = Vector(1, 1);
	Delta = Delta * (((rand() % 200)/100.0) - 1) * 100 * Factor;
	Position += Delta;
}
std::string AIActionMove::Description()
{
	return "Move to vector, " + std::to_string(Position.X) + ":" + std::to_string(Position.Y);
}