#include "CBRCase.h"
#include "AIActionMove.h"
#include <sstream>

CBRCase::CBRCase()
{
	Validity = 0;
	CalculatedValueEnd = 0;
	CalculatedValueStart = 0;
	ExecutionTime = 0;
	//DeltaMovement = Vector();
	MoveTowards = 0;
	MoveNormal = 0;
	DeltaValue = 0;
}


CBRCase::~CBRCase()
{
	//while (Moves.size() > 0)
	//{
		//delete Moves.back();
	//	Moves.pop_back();
	//}
}

void CBRCase::RandomiseMoves()
{
	float Factor = 1;
	int MaxMove = 500;
	int MaxLook = 520;
	int actions = 1 + (rand() % 2);
	MutateCases(Factor);
	/*for (int i = 0; i < actions; ++i)
	{
		//Add random action
		switch ((int)roundf(rand() % 2))
		{
		case 0:
			Moves.push_back(new AIActionMove(NULL, Vector()));
			break;
		case 1:
			if (Moves.size() > 0) {
				delete Moves.back();
				Moves.pop_back();
			}
			break;
		}
		if (Moves.size() > 0) {
			Moves.back()->Mutate(Factor);
		}
	}
	if (Moves.size() > 2) {
		delete Moves.back();
		Moves.pop_back();
	}*/
}
float& CBRCase::GetOutputParams(int id)
{
	switch (id)
	{
	case 0:
		return MoveNormal;
	case 1:
		return MoveTowards;
	}
}
void CBRCase::MutateCases(float subfactor)
{
	/*float MaxMoveRand = 1;
	float Factor = MaxMoveRand * subfactor * (((rand() % 200) / 100.0) - 1);
	DeltaMovement.X += Factor;
	Factor = MaxMoveRand * subfactor * (((rand() % 200) / 100.0) - 1);
	DeltaMovement.Y += Factor;
	float MaxMove = 100;
	if (abs(DeltaMovement.X) > MaxMove) {
		DeltaMovement.X = copysignf(MaxMove, DeltaMovement.X);
	}
	if (abs(DeltaMovement.Y) > MaxMove) {
		DeltaMovement.Y = copysignf(MaxMove,DeltaMovement.Y);
	}
	if (isnan(DeltaMovement.X)) { DeltaMovement.X = 0; }
	if (isnan(DeltaMovement.Y)) { DeltaMovement.Y = 0; }*/
	float MaxMoveRand = 0.8;
	float Factor = MaxMoveRand * subfactor * (((rand() % 200) / 100.0) - 1);
	MoveTowards += Factor;
	Factor = MaxMoveRand * subfactor * (((rand() % 200) / 100.0) - 1);
	MoveNormal += Factor;

	if (abs(MoveTowards) > 1) {
		MoveTowards = copysignf(1, MoveTowards);
	}
	if (abs(MoveNormal) > 1) {
		MoveNormal = copysignf(1, MoveNormal);
	}

}
void CBRCase::ApplyActionsToEntity(EntityWolf * entity)
{
	entity->MoveNormal = MoveNormal;
	entity->MoveTowards = MoveTowards;
	//entity->TargetLocation = entity->Pos + DeltaMovement;
	/*entity->ClearAIStack();
	//std::cout << "Starting ai routine" << std::endl;
	for (int i = 0; i < Moves.size(); ++i)
	{
		entity->AIStack.push(Moves.at(i)->CopySelf(entity));
		//std::cout << (Moves.at(i))->Description() << std::endl;
	}*/
}
std::ostream& operator<<(std::ostream& ios, const CBRCase& cbrc)
{
	ios << cbrc.CalculatedValueEnd \
	<< cbrc.CalculatedValueStart\
	<< cbrc.Validity\
	<< cbrc.MoveNormal\
	<< cbrc.MoveTowards\
	<< cbrc.EnviromentStart\
	<< cbrc.EnviromentEnd;
	return ios;
}
std::istream& operator>>(std::istream& ios, CBRCase& cbrc)
{
	ios >> cbrc.CalculatedValueEnd\
		>> cbrc.CalculatedValueStart \
		>> cbrc.Validity \
		>> cbrc.MoveNormal \
		>> cbrc.MoveTowards \
		>> cbrc.EnviromentStart \
		>> cbrc.EnviromentEnd;
	return ios;
}
void CBRCase::CopyCaseAction(CBRCase*c) {
	MoveTowards = c->MoveTowards;
	MoveNormal = c->MoveNormal;
}