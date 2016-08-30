#include "CBRInstance.h"



CBRInstance::CBRInstance()
{
	this->CaseBase = std::vector<CBRCase*>();
	SearchDistanceThreshold = 15;
	UnclaimedOtherPenalty = 1;
	DistanceWeights = CBRWeightDistance();
	ValueWeights = CBRWeightValue();
}


CBRInstance::~CBRInstance()
{
}

float CBRInstance::DistanceInfo(EntityInfo a, EntityInfo b)
{
	float DistanceTemp = 0;
	float Distance = 0;
	int WeightIter = 0;
	Vector dist = a.Position - b.Position;
	DistanceTemp = DistanceWeights.Position * sqrt(dist.Dot(dist));
	Distance += DistanceTemp * DistanceTemp;
	DistanceTemp = DistanceWeights.Distance * abs(a.Distance - b.Distance);
	Distance += DistanceTemp * DistanceTemp;
	return sqrt(Distance);
}
bool CBRInstance::AllPairsComp(float * a, float * b)
{
	return a[1] < b[1];
}
float CBRInstance::Distance(CBREnvironment a, CBREnvironment b)
{
	float TempDistance = 0;
	float Distance = 0;
	TempDistance = DistanceInfo(a.Self, b.Self);
	Distance += TempDistance * TempDistance;
	TempDistance = DistanceInfo(a.Herd, b.Herd);
	Distance += TempDistance * TempDistance;
	return sqrt(Distance);
}

void CBRInstance::Load(std::string loc)
{

}
CBRCase * CBRInstance::GetCase(CBREnvironment sitrep)
{
	float ClosestDistance = 0;
	int ClosestCase = -1;
	float NewDist;
	for (int i = 0; i < CaseBase.size();++i)
	{
		if (ClosestCase == -1)
		{
			ClosestCase = i;
			ClosestDistance = Distance(sitrep, CaseBase.at(i)->EnviromentStart);
		}
		else
		{
			NewDist = Distance(sitrep, CaseBase.at(i)->EnviromentStart);
			if (abs(NewDist) < abs(ClosestDistance))
			{
				ClosestDistance = NewDist;
				ClosestCase = i;
			}
		}
	}
	CBRCase * NewCase = new CBRCase();
	NewCase->EnviromentStart = sitrep;
	NewCase->CalculatedValueStart = CalculateValue(sitrep);
	if (ClosestCase == -1)
	{
		//Gen a random case
		NewCase->RandomiseMoves();
		std::cout << "Random moves" << std::endl;
	}
	else {
		for (int i = 0; i < CaseBase[ClosestCase]->Moves.size(); ++i)
		{
			NewCase->Moves.push_back(CaseBase.at(ClosestCase)->Moves[i]->CopySelf(NULL));
		}
		if (ClosestDistance > SearchDistanceThreshold)
		{
			//Gen a partialy random case
			//ISSUES
			NewCase->MutateCases(0.1);
			if (rand() % 4 == 0)
			{
				NewCase->RandomiseMoves();
			}
			std::cout << "Previouse case" << std::endl;
		}
		else
		{
			//Adapt previouse cases for new enviroment
			NewCase->MutateCases(0.5 * ClosestDistance);
			if (rand() % 2 == 0)
			{
				NewCase->RandomiseMoves();
			}
			std::cout << "Partialy random case" << std::endl;
		}
	}
	return NewCase;
}
float CBRInstance::CalculateValue(CBREnvironment a)
{
	float Value = 0;
	float ValueTemp = 0;
	//ValueTemp = ValueWeights.DistanceFromClosest * abs(a.Self.DistanceFromClosest);
	ValueTemp = ValueWeights.Distance * abs(a.Self.Distance);
	Value += ValueTemp * ValueTemp;
	//ValueTemp = ValueWeights.Health * (
	return sqrt(Value);
}
void CBRInstance::FeedBackCase(CBRCase * feedback)
{
	//To start with, find the case it came from
	//Then if the end results are similar add to the validity
	//Otherwise decrement validity
	float ClosestDistance = 0;
	int ClosestCase = -1;
	float NewDist;
	bool Feedbackneeded = false;
	for (int i = 0; i < CaseBase.size(); ++i)
	{
		if (ClosestCase == -1)
		{
			ClosestCase = i;
			ClosestDistance = Distance(feedback->EnviromentStart, CaseBase.at(i)->EnviromentStart);
		}
		else
		{
			NewDist = Distance(feedback->EnviromentStart, CaseBase.at(i)->EnviromentStart);
			if (abs(NewDist) < abs(ClosestDistance))
			{
				ClosestDistance = NewDist;
				ClosestCase = i;
			}
		}
	}
	if (ClosestCase == -1)
	{
		//Gen a random case
		this->CaseBase.push_back(feedback);
		Feedbackneeded = true;
	}
	else {
		if (ClosestDistance > SearchDistanceThreshold)
		{
			//Gen a partialy random case
			this->CaseBase.push_back(feedback);
			Feedbackneeded = true;
		}
		else
		{
			//Adapt previouse cases for new enviroment		
			float Dist = Distance(feedback->EnviromentEnd, CaseBase.at(ClosestCase)->EnviromentEnd);
			if (Dist < ValidityDistanceThreshold)
			{
				++this->CaseBase.at(ClosestCase)->Validity;
			}
			else
			{
				--this->CaseBase.at(ClosestCase)->Validity;
				if (this->CaseBase.at(ClosestCase)->CalculatedValueEnd < feedback->CalculatedValueEnd)
				{
					std::cout << "Found Better case" << std::endl;
					delete this->CaseBase.at(ClosestCase);
					this->CaseBase.at(ClosestCase) = feedback;
					Feedbackneeded = true;
				}
			}
		}
	}
	if (!Feedbackneeded)
	{
		delete feedback;
	}
}