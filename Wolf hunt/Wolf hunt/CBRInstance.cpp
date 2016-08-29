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
	DistanceTemp = DistanceWeights.FlashTime * abs(a.FlashTime - b.FlashTime);
	Distance += DistanceTemp * DistanceTemp;
	Vector dist = a.Position - b.Position;
	DistanceTemp = DistanceWeights.Position * sqrt(dist.Dot(dist));
	Distance += DistanceTemp * DistanceTemp;
	DistanceTemp = DistanceWeights.Rotation * abs(Entity::AngleDifference(a.Rot,b.Rot));
	Distance += DistanceTemp * DistanceTemp;
	return sqrt(Distance);
}
bool CBRInstance::AllPairsComp(float * a, float * b)
{
	return a[1] < b[1];
}
float CBRInstance::Distance(CBREnvironment a, CBREnvironment b)
{
	float Distance = 0;
	Distance += DistanceInfo(a.Self, b.Self);
	//Distance += DistanceInfo(a.Player, b.Player);
	//Analyse "other factors" this system generates pairs of entities
	/*
	For each element in a, find distance to each element in b
	if the distance is smaller than that items current distance, claim it - if the distance is too great it cannot be claimed
	an entity can only be claimed if they are the same type
	*/
	//0 is distance,1 is claiment in a
	/*std::vector<std::vector<float*>> DistanceFromEachA;
	std::vector<std::vector<int>> ClosestToB;
	for (int i = 0; i < a.OtherFactors.size(); ++i)
	{
		std::vector<float*> TempDistances;
		for (int j = 0; j < b.OtherFactors.size(); ++j)
		{
			float NewDistance;
			int Claiment = -1;
			EntityInfo bOtherInfo = b.OtherFactors.at(i);
			EntityInfo aOtherInfo = a.OtherFactors.at(j);
			if (bOtherInfo.Type != aOtherInfo.Type)
			{
				float Distance = DistanceInfo(aOtherInfo, bOtherInfo);
				if (Distance < MaxArrayClaimentThreshold)
				{
					NewDistance = Distance;
					Claiment = j;
				}
			}
			TempDistances.push_back(new float[2]{ NewDistance,(float)Claiment });
		}
		DistanceFromEachA.push_back(TempDistances);
	}
	for (int i = 0; i < b.OtherFactors.size(); ++i)
	{
		float ClosestDistance;
		int ClosestClaiment = -1;
		for (int j = 0; j < a.OtherFactors.size(); ++j)
		{
			EntityInfo bOtherInfo = b.OtherFactors.at(i);
			EntityInfo aOtherInfo = a.OtherFactors.at(j);
			if (bOtherInfo.Type != aOtherInfo.Type)
			{
				float Distance = DistanceInfo(bOtherInfo, aOtherInfo);
				if (Distance < MaxArrayClaimentThreshold)
				{
					if (ClosestClaiment == -1)
					{
						ClosestDistance = Distance;
						ClosestClaiment = j;
					}else if (Distance < ClosestDistance)
					{
						ClosestDistance = Distance;
						ClosestClaiment = j;
					}
				}
			}
		}
		ClosestToB.at(i).push_back(ClosestClaiment);
	}
	//Sort Distance to a
	std::sort(DistanceFromEachA.front(), DistanceFromEachA.back(),CBRInstance::AllPairsComp);
	//For each entity on A, find the closest B, if the closest A from that B is the first ent -> Remove both pairs
	int i = 0;
	while (i++ < DistanceFromEachA.size())
	{
		for (int j = 0; j < DistanceFromEachA.at(i).size(); ++j)
		{
			if(ClosestToB.at(j) == Distance)
		}
	}*/

	return Distance;
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
	ValueTemp = ValueWeights.FlashTime * abs(a.Self.FlashTime);
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
				if (this->CaseBase.at(ClosestCase)->CalculatedValueEnd > feedback->CalculatedValueEnd)
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