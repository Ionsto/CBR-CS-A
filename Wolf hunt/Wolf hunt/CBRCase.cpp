#include "CBRCase.h"
#include "AIActionMove.h"
#include <sstream>

CBRCase::CBRCase()
{
	Validity = 0;
	CalculatedValueEnd = 0;
	CalculatedValueStart = 0;
	ExecutionTime = 0;
	DeltaMovement = Vector();
	DeltaValue = 0;
}


CBRCase::~CBRCase()
{
	while (Moves.size() > 0)
	{
		delete Moves.back();
		Moves.pop_back();
	}
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
void CBRCase::MutateCases(float subfactor)
{
	float Factor = subfactor * (((rand() % 200)/100.0)-1);
	DeltaMovement = DeltaMovement + Vector(0, rand() % 50)*Factor;
	float MaxMove = 100;
	if (abs(DeltaMovement.X) > MaxMove) {
		DeltaMovement.X = copysignf(MaxMove, DeltaMovement.X);
	}
	if (abs(DeltaMovement.Y) > MaxMove) {
		DeltaMovement.Y = copysignf(MaxMove,DeltaMovement.Y);
	}
	//for (int i = 0; i < Moves.size(); ++i)
	//{
	//	(Moves[i])->Mutate(Factor);
	//}
}
void CBRCase::ApplyActionsToEntity(EntityWolf * entity)
{
	entity->TargetLocation = entity->Pos + DeltaMovement;
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
	<< cbrc.DeltaMovement.X\
	<< cbrc.DeltaMovement.Y\
	<< cbrc.EnviromentStart\
	<< cbrc.EnviromentEnd;
	return ios;
}
std::istream& operator>>(std::istream& ios, CBRCase& cbrc)
{
	ios >> cbrc.CalculatedValueEnd\
		>> cbrc.CalculatedValueStart \
		>> cbrc.Validity \
		>> cbrc.DeltaMovement.X \
		>> cbrc.DeltaMovement.Y \
		>> cbrc.EnviromentStart \
		>> cbrc.EnviromentEnd;
	return ios;
}