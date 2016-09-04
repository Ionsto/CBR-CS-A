#include "CBRInstance.h"
#include <vector>
#include <algorithm>
#define DivZero(a,b) (b == 0 ? 10000 : a/b)

CBRInstance::CBRInstance()
{
	this->CaseBase = std::vector<CBRCase*>();
	MinInsertionThreshold = 100;
	IdenticalCaseThreshold = 100;
	NearestNeighborDistance = 500;
	ValidityDistanceThreshold = 50;
	UnclaimedOtherPenalty = 1;
	DistanceWeights = CBRWeightDistance();
	ValueWeights = CBRWeightValue();
	NearestNeighborDistance = 100;
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
//Minimise
float CBRInstance::Distance(CBREnvironment a, CBREnvironment b)
{
	float TempDistance = 0;
	float Distance = 0;
	TempDistance = a.Herd.Position.X - b.Herd.Position.X;// DistanceInfo(a.Self, b.Self);
	Distance += TempDistance * TempDistance;
	TempDistance = a.Herd.Position.Y - b.Herd.Position.Y;// DistanceInfo(a.Self, b.Self);
	Distance += TempDistance * TempDistance;
	//TempDistance = DistanceInfo(a.Herd, b.Herd);
	//Distance += TempDistance * TempDistance;
	return sqrt(Distance);
}
void CBRInstance::WeightedLinearRegression(std::vector<CBRCase*> cases, int paramx, int paramy, float * intercept, float * gradient, float * error)
{
}
void CBRInstance::Save(std::string loc)
{

}
void CBRInstance::Load(std::string loc)
{

}
CBRCase * CBRInstance::GetCase(CBREnvironment sitrep)
{
	std::vector<ClosePair> NearbyCases;
	float distance = 0;
	for (int i = 0; i < CaseBase.size(); ++i)
	{
		distance = Distance(sitrep, CaseBase.at(i)->EnviromentStart);
		if (distance < NearestNeighborDistance)
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
		NewCase->DeltaMovement = CaseBase[NearbyCases.at(0).CloseCase]->DeltaMovement;
		for (int i = 0; i < CaseBase[NearbyCases.at(0).CloseCase]->Moves.size(); ++i)
		{
			NewCase->Moves.push_back(CaseBase.at(NearbyCases.at(0).CloseCase)->Moves[i]->CopySelf(NULL));
		}
		if (NearbyCases.at(0).NewDist < IdenticalCaseThreshold)
		{
			NewCase->MutateCases(CaseBase[NearbyCases.at(0).CloseCase]->CalculatedValueEnd * 0.01);
			if (rand() % 2 == 0)
			{
				//NewCase->RandomiseMoves();
			}
			std::cout << "Partialy random case" << std::endl;
		}
		else
		{
			//Use linear regression of moves
			//First we must compress the n dimentioned radius thing onto a 2d plane, where our regression will excel
			/*float Gradient = 0;
			float Intercept = 0;
			float MX = 0, MY = 0;
			float SYY = 0, SXX = 0, SXSQRD = 0;
			int n = NearbyCases.size();
			for (int IterParam = 0; IterParam < 3; ++IterParam)
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
			}*/
			float MeanError = 0;
			int InParamCount = 3;
			int OutParamCount = 2;
			int NearbyCasesCount = NearbyCases.size();
			for (int InParam = 0; InParam < InParamCount; ++InParam)
			{
				for (int OutParam = 0; OutParam < OutParamCount; ++OutParam)
				{
					float xw = 0;
					float x = 0;
					float yw = 0;
					float y = 0;
					float a = 0;
					float b = 0;
					float SSres = 0;
					float SStotal = 0;
					float ExpectedY = 0;
					float rsqd = 0;
					// compute the weighted averages
					for (int i = 0; i < NearbyCasesCount; i++)
					{
						xw += CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.GetInputParams(InParam) * DivZero(1, CaseBase[NearbyCases[i].CloseCase]->CalculatedValueEnd);
						yw += CaseBase[NearbyCases[i].CloseCase]->GetOutputParams(OutParam) * DivZero(1, CaseBase[NearbyCases[i].CloseCase]->CalculatedValueEnd);
						x += CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.GetInputParams(InParam);
						y += CaseBase[NearbyCases[i].CloseCase]->GetOutputParams(OutParam);
					}
					double weightedX = DivZero(xw, x);
					double weightedY = DivZero(yw, y);

					// compute the gradient and intercept
					for (int i = 0; i < NearbyCasesCount; i++)
					{
						a += (CaseBase[NearbyCases[i].CloseCase]->GetOutputParams(OutParam) - weightedY) * (CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.GetInputParams(InParam) - weightedX) * CaseBase[NearbyCases[i].CloseCase]->CalculatedValueEnd;
							b += (CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.GetInputParams(InParam) - weightedX) * (CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.GetInputParams(InParam) - weightedX) * CaseBase[NearbyCases[i].CloseCase]->CalculatedValueEnd;
					}
					double gradient = DivZero(a, b);
					double intercept = (weightedY - weightedX) * gradient;
					//var string = 'y = ' + Math.round(gradient*100) / 100 + 'x + ' + Math.round(intercept*100) / 100;
					//var results = [];

					for (int i = 0; i < NearbyCasesCount; i++)
					{
						ExpectedY = (gradient * CaseBase[NearbyCases[i].CloseCase]->EnviromentStart.GetInputParams(InParam)) + intercept;
						SSres += (CaseBase[NearbyCases[i].CloseCase]->GetOutputParams(OutParam) - weightedY) * (CaseBase[NearbyCases[i].CloseCase]->GetOutputParams(OutParam) - weightedY);
						SSres += (CaseBase[NearbyCases[i].CloseCase]->GetOutputParams(OutParam) - ExpectedY) * (CaseBase[NearbyCases[i].CloseCase]->GetOutputParams(OutParam) - ExpectedY);
						MeanError += CaseBase[NearbyCases[i].CloseCase]->CalculatedValueEnd;
					}
					//MeanError = DivZero(MeanError, NearbyCasesCount);
					rsqd = 1 - DivZero(SSres, SStotal);
					//gradient, intercept, MeanError
					NewCase->GetOutputParams(OutParam) += intercept + (gradient * NewCase->EnviromentStart.GetInputParams(InParam));
				}
			}
			MeanError /= NearbyCasesCount;
			for (int OutParam = 0; OutParam < OutParamCount; ++OutParam)
			{
				NewCase->GetOutputParams(OutParam) = NewCase->GetOutputParams(OutParam) / OutParamCount;
			}
			NewCase->MutateCases(MeanError * 0.5);
		}
	}
	if (NewCase->CalculatedValueStart - NewCase->CalculatedValueEnd < 0)
	{
		NewCase->MutateCases(1);
	}
	return NewCase;
}
//Needs to minimise
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
		this->CaseBase.push_back(feedback);
		Feedbackneeded = true;
	}
	else {
		if (ClosestDistance > MinInsertionThreshold)
		{
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
				if (feedback->DeltaValue < this->CaseBase.at(ClosestCase)->DeltaValue)
				{
					std::cout << "Found Better case" << std::endl;
					delete this->CaseBase.at(ClosestCase);
					this->CaseBase.at(ClosestCase) = feedback;
					Feedbackneeded = true;
				}
				else if (this->CaseBase.at(ClosestCase)->Validity < 0)
				{
					delete this->CaseBase.at(ClosestCase);
					this->CaseBase.erase(CaseBase.begin() + ClosestCase);
				}
			}
			//}
		}
	}
	if (!Feedbackneeded)
	{
		delete feedback;
	}
}