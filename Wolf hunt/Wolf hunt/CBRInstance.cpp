#include "CBRInstance.h"
#include <vector>
#include <algorithm>


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
	float EvalDistance = 100;
	struct ClosePair {
		float NewDist;
		int CloseCase;
		ClosePair(float d, int cc) { NewDist = d; CloseCase = cc; };
		static bool SortComp(ClosePair a, ClosePair b)
		{
			return a.NewDist < b.NewDist;
		}
	};
	std::vector<ClosePair> NearbyCases;
	float distance = 0;
	for (int i = 0; i < CaseBase.size(); ++i)
	{
		distance =Distance(sitrep, CaseBase.at(i)->EnviromentStart);
		if (distance < EvalDistance)
		{
			NearbyCases.push_back(ClosePair(distance, i));
		}
	}
	std::sort(NearbyCases.begin(), NearbyCases.end(),ClosePair::SortComp);
	CBRCase * NewCase = new CBRCase();
	NewCase->EnviromentStart = sitrep;
	NewCase->CalculatedValueStart = CalculateValue(sitrep);
	if (NearbyCases.size() == 0)
	{
		NewCase->RandomiseMoves();
		std::cout << "Random moves" << std::endl;
	}
	else
	{
		for (int i = 0; i < CaseBase[NearbyCases.at(0).CloseCase]->Moves.size(); ++i)
		{
			NewCase->Moves.push_back(CaseBase.at(NearbyCases.at(0).CloseCase)->Moves[i]->CopySelf(NULL));
		}
		if (NearbyCases.at(0).NewDist < SearchDistanceThreshold)
		{
			NewCase->MutateCases(0.01 * (0.1 + NearbyCases.at(0).NewDist));
			if (rand() % 2 == 0)
			{
				NewCase->RandomiseMoves();
			}
			std::cout << "Partialy random case" << std::endl;
		}
		else
		{
			//Use linear regression of moves
			//First we must compress the n dimentioned radius thing onto a 2d plane, where our regression will excel
			float Gradient = 0;
			float Intercept = 0;
			float MX = 0, MY = 0;
			float SYY = 0, SXX = 0, SXSQRD = 0;
			int n = NearbyCases.size();
			for (int IterParam = 0; IterParam < 1; ++IterParam)
			{
				for (int i = 0; i < n; ++i)
				{
					float ParamOffset = CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.SelectParam(IterParam) - NewCase->EnviromentStart.SelectParam(IterParam);
					MX += ParamOffset;
					MY += NewCase->DeltaMovement.X;
				}
				MX /= n;
				MY /= n;
				for (int i = 0; i < n; ++i)
				{
					float x = CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.SelectParam(IterParam) - NewCase->EnviromentStart.SelectParam(IterParam);
					float y = NewCase->DeltaMovement.X;
					SXX += (x - MX) * (y - MY);
					SXSQRD += (x - MX) * (x - MX);
				}
				Gradient = SXX / SXSQRD;
				Intercept = MY - (Gradient * MX);
				NewCase->DeltaMovement.X = Intercept;
			}
			Gradient = 0;
			Intercept = 0;
			MX = 0, MY = 0;
			SYY = 0, SXX = 0, SXSQRD = 0;
			for (int IterParam = 0; IterParam < 1; ++IterParam)
			{
				for (int i = 0; i < n; ++i)
				{
					float ParamOffset = CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.SelectParam(IterParam) - NewCase->EnviromentStart.SelectParam(IterParam);
					MX += ParamOffset;
					MY += NewCase->DeltaMovement.Y;
				}
				MX /= n;
				MY /= n;
				for (int i = 0; i < n; ++i)
				{
					float x = CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.SelectParam(IterParam) - NewCase->EnviromentStart.SelectParam(IterParam);
					float y = NewCase->DeltaMovement.X;
					SXX += (x - MX) * (y - MY);
					SXSQRD += (x - MX) * (x - MX);
				}
				Gradient = SXX / SXSQRD;
				Intercept = MY - (Gradient * MX);
				NewCase->DeltaMovement.Y = Intercept;
			}

			NewCase->MutateCases(1);
		}
	}
	if (NewCase->CalculatedValueStart - NewCase->CalculatedValueEnd < 0)
	{
		NewCase->MutateCases(1);
	}
	/*
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
			NewCase->MutateCases(0.5 * (0.1 + ClosestDistance));
			if (rand() % 2 == 0)
			{
				NewCase->RandomiseMoves();
			}
			std::cout << "Partialy random case" << std::endl;
		}
	}*/
	return NewCase;
}
float CBRInstance::CalculateValue(CBREnvironment a)
{
	float Value = 0;
	float ValueTemp = 0;
	//ValueTemp = ValueWeights.DistanceFromClosest * abs(a.Self.DistanceFromClosest);
	ValueTemp = ValueWeights.Distance * abs(a.Herd.Distance);
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
	std::cout << feedback->CalculatedValueEnd << std::endl;
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
				if (this->CaseBase.at(ClosestCase)->CalculatedValueEnd - this->CaseBase.at(ClosestCase)->CalculatedValueStart < feedback->CalculatedValueEnd - feedback->CalculatedValueStart)
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